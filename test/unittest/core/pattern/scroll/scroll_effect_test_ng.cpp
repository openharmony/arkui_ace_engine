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

#include "mock_task_executor.h"
#include "scroll_test_ng.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/unittest/core/pattern/scrollable/scrollable_test_utils.h"

#include "core/components_ng/pattern/scroll/effect/scroll_fade_effect.h"
#include "core/components_ng/pattern/scroll/scroll_spring_effect.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"

namespace OHOS::Ace::NG {
namespace {} // namespace

class ScrollEffectTestNg : public ScrollTestNg {
public:
    RefPtr<ScrollPaintMethod> UpdateContentModifier();
};

RefPtr<ScrollPaintMethod> ScrollEffectTestNg::UpdateContentModifier()
{
    auto paintWrapper = frameNode_->CreatePaintWrapper();
    RefPtr<ScrollPaintMethod> paintMethod = AceType::DynamicCast<ScrollPaintMethod>(paintWrapper->nodePaintImpl_);
    paintMethod->UpdateContentModifier(AceType::RawPtr(paintWrapper));
    return paintMethod;
}

/**
 * @tc.name: SpringEffect001
 * @tc.desc: Test SpringEffect
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, SpringEffect001, TestSize.Level1)
{
    auto springEffect = AceType::MakeRefPtr<ScrollSpringEffect>();
    springEffect->ProcessScrollOver(0.0);
    EXPECT_EQ(springEffect->scrollable_, nullptr);

    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateContent();
    CreateScrollDone();
    springEffect = AceType::DynamicCast<ScrollSpringEffect>(pattern_->GetScrollEdgeEffect());
    auto scrollable = AceType::MakeRefPtr<Scrollable>();
    springEffect->SetScrollable(scrollable);
    springEffect->ProcessScrollOver(0.0);
    EXPECT_NE(springEffect->scrollable_->GetSpringProperty(), nullptr);

    springEffect->scrollable_->springOffsetProperty_ = nullptr;
    scrollable->MarkAvailable(false);
    springEffect->ProcessScrollOver(0.0);
    EXPECT_NE(springEffect->scrollable_->GetSpringProperty(), nullptr);

    springEffect->scrollable_->springOffsetProperty_ = nullptr;
    pattern_->SetDirection(FlexDirection::ROW_REVERSE);
    pattern_->SetEdgeEffect(EdgeEffect::SPRING);
    springEffect->ProcessScrollOver(0.0);
    EXPECT_NE(springEffect->scrollable_->GetSpringProperty(), nullptr);

    springEffect->SetScrollable(nullptr);
    springEffect->ProcessScrollOver(0.0);
    springEffect->initTrailingCallback_ = nullptr;
    springEffect->ProcessScrollOver(0.0);
    springEffect->initLeadingCallback_ = nullptr;
    springEffect->ProcessScrollOver(0.0);
    springEffect->trailingCallback_ = nullptr;
    springEffect->ProcessScrollOver(0.0);
    springEffect->initTrailingCallback_ = nullptr;
    springEffect->ProcessScrollOver(0.0);
    springEffect->currentPositionCallback_ = nullptr;
    springEffect->ProcessScrollOver(0.0);
    EXPECT_EQ(springEffect->scrollable_, nullptr);
}

/**
 * @tc.name: SpringEffect002
 * @tc.desc: Test SpringEffect
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, SpringEffect002, TestSize.Level1)
{
    auto springEffect = AceType::MakeRefPtr<ScrollSpringEffect>();
    springEffect->ProcessSpringUpdate();
    EXPECT_EQ(springEffect->scrollable_, nullptr);

    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateContent();
    CreateScrollDone();
    springEffect = AceType::DynamicCast<ScrollSpringEffect>(pattern_->GetScrollEdgeEffect());
    auto scrollable = AceType::MakeRefPtr<Scrollable>();
    springEffect->SetScrollable(scrollable);
    springEffect->ProcessSpringUpdate();
    EXPECT_EQ(springEffect->scrollable_->state_, Scrollable::AnimationState::IDLE);

    scrollable->MarkAvailable(false);
    springEffect->ProcessSpringUpdate();
    EXPECT_EQ(springEffect->scrollable_->state_, Scrollable::AnimationState::IDLE);

    pattern_->SetDirection(FlexDirection::ROW_REVERSE);
    pattern_->SetEdgeEffect(EdgeEffect::SPRING);
    springEffect->ProcessSpringUpdate();
    EXPECT_EQ(springEffect->scrollable_->state_, Scrollable::AnimationState::IDLE);

    springEffect->SetScrollable(nullptr);
    springEffect->ProcessSpringUpdate();
    springEffect->initTrailingCallback_ = nullptr;
    springEffect->ProcessSpringUpdate();
    springEffect->initLeadingCallback_ = nullptr;
    springEffect->ProcessSpringUpdate();
    springEffect->trailingCallback_ = nullptr;
    springEffect->ProcessSpringUpdate();
    springEffect->initTrailingCallback_ = nullptr;
    springEffect->ProcessSpringUpdate();
    springEffect->currentPositionCallback_ = nullptr;
    springEffect->ProcessSpringUpdate();
    EXPECT_EQ(springEffect->scrollable_, nullptr);
}

/**
 * @tc.name: ScrollFadeEffect001
 * @tc.desc: Test the correlation function in ScrollFadeEffect under different conditions.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, ScrollFadeEffect001, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::FADE, true);
    CreateContent(600.f);
    CreateScrollDone();
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
    const SizeF viewPort(WIDTH, HEIGHT);
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
    // maxExtent: ITEM_MAIN_SIZE * 2
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(ITEM_MAIN_SIZE, true), 0.0));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(0.0, true), 0.0));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(-ITEM_MAIN_SIZE, true), 0.0));

    ScrollTo(ITEM_MAIN_SIZE * 1);
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(ITEM_MAIN_SIZE * 2, true), 0.0));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(0.0, true), 0.0));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(-ITEM_MAIN_SIZE * 2, true), 0.0));

    ScrollTo(ITEM_MAIN_SIZE * 2);
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(ITEM_MAIN_SIZE, true), 0.0));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(0.0, true), 0.0));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(-ITEM_MAIN_SIZE, true), 0.0));

    pattern_->currentOffset_ = ITEM_MAIN_SIZE;
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(ITEM_MAIN_SIZE, true), -ITEM_MAIN_SIZE));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(0.0, true), -ITEM_MAIN_SIZE));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(-ITEM_MAIN_SIZE * 2, true), 0.0));

    pattern_->currentOffset_ = -ITEM_MAIN_SIZE;
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(ITEM_MAIN_SIZE * 2, true), 0.0));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(0.0, true), 0.0));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(-ITEM_MAIN_SIZE, true), 0.0));

    // over scroll
    pattern_->currentOffset_ = -ITEM_MAIN_SIZE * 3;
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(ITEM_MAIN_SIZE * 2, true), ITEM_MAIN_SIZE));

    // crash the bottom
    pattern_->currentOffset_ = -ITEM_MAIN_SIZE * 3;
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(ITEM_MAIN_SIZE, true), ITEM_MAIN_SIZE));
    pattern_->currentOffset_ = -ITEM_MAIN_SIZE * 3;
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(ITEM_MAIN_SIZE, false), 0.0));
    pattern_->currentOffset_ = -ITEM_MAIN_SIZE * 3;
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(ITEM_MAIN_SIZE * 3, false), 0.0));
}

/**
 * @tc.name: ScrollFadeEffect002
 * @tc.desc: Test Paint
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, ScrollFadeEffect002, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::FADE, true);
    CreateContent(100.f);
    CreateScrollDone();
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
    scrollFadeEffect->Paint(rsCanvas, SizeF(0, 1), offset);
    EXPECT_CALL(rsCanvas, DetachPen).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachBrush).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, ClipRect).Times(1);
    EXPECT_CALL(rsCanvas, DrawCircle).Times(1);
    scrollFadeEffect->fadePainter_->direction_ = OverScrollDirection::RIGHT;
    scrollFadeEffect->Paint(rsCanvas, SizeF(1, 1), offset);
}

/**
 * @tc.name: ScrollFadeEffect003
 * @tc.desc: Test SetPaintDirection in different situations.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, ScrollFadeEffect003, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::FADE, true);
    CreateContent();
    CreateScrollDone();
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
HWTEST_F(ScrollEffectTestNg, ScrollFadeEffect004, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::FADE, true);
    CreateContent();
    CreateScrollDone();
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
HWTEST_F(ScrollEffectTestNg, ScrollFadeEffect005, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::FADE, true);
    CreateContent();
    CreateScrollDone();
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
    const SizeF viewPort(WIDTH, HEIGHT);
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
HWTEST_F(ScrollEffectTestNg, FadeController001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ScrollFadeController and set callback function.
     */
    auto mockTaskExecutor = AceType::MakeRefPtr<MockScrollTaskExecutor>();
    MockPipelineContext::GetCurrentContext()->taskExecutor_ = mockTaskExecutor;
    auto fadeController = AceType::MakeRefPtr<ScrollFadeController>();
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
    mockTaskExecutor->RunDelayTask();
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
    mockTaskExecutor->RunDelayTask();
    fadeController->decele_->NotifyListener(100.0);
    EXPECT_EQ(param1, 2940.3);
    EXPECT_EQ(param2, 31853.25);
}

/**
 * @tc.name: FadeController002
 * @tc.desc: Test scroll_fade_controller
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, FadeController002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ScrollFadeController and set callback function.
     */
    auto mockTaskExecutor = AceType::MakeRefPtr<MockScrollTaskExecutor>();
    MockPipelineContext::GetCurrentContext()->taskExecutor_ = mockTaskExecutor;
    auto fadeController = AceType::MakeRefPtr<ScrollFadeController>();
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
    mockTaskExecutor->RunDelayTask();
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
HWTEST_F(ScrollEffectTestNg, FadeController003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ScrollFadeController and set callback function.
     */
    auto fadeController = AceType::MakeRefPtr<ScrollFadeController>();
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
HWTEST_F(ScrollEffectTestNg, EdgeEffectOption001, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, false);
    CreateContent(HEIGHT);
    CreateScrollDone();
    EXPECT_FALSE(pattern_->GetAlwaysEnabled());
    EXPECT_FALSE(pattern_->GetScrollableEvent()->GetEnabled());
}

/**
 * @tc.name: EdgeEffectOption002
 * @tc.desc: Test EdgeEffectOption
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, EdgeEffectOption002, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateContent(HEIGHT);
    CreateScrollDone();
    EXPECT_TRUE(pattern_->GetAlwaysEnabled());
    EXPECT_TRUE(pattern_->GetScrollableEvent()->GetEnabled());
}

/**
 * @tc.name: EdgeEffectOption003
 * @tc.desc: Test EdgeEffectOption
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, EdgeEffectOption003, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, false);
    // 20 is childNumber.
    CreateContent(2000.f);
    CreateScrollDone();
    EXPECT_FALSE(pattern_->GetAlwaysEnabled());
    EXPECT_TRUE(pattern_->GetScrollableEvent()->GetEnabled());
}

/**
 * @tc.name: EdgeEffectOption004
 * @tc.desc: Test EdgeEffectOption
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, EdgeEffectOption004, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    // 20 is childNumber.
    CreateContent(2000.f);
    CreateScrollDone();
    EXPECT_TRUE(pattern_->GetAlwaysEnabled());
    EXPECT_TRUE(pattern_->GetScrollableEvent()->GetEnabled());
}

/**
 * @tc.name: ContentClip001
 * @tc.desc: Test ContentClip
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, ContentClip001, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    CreateContent(2000.f);
    CreateScrollDone();

    paintProperty_->UpdateContentClip({ ContentClipMode::DEFAULT, nullptr });
    auto ctx = AceType::DynamicCast<MockRenderContext>(frameNode_->GetRenderContext());
    ASSERT_TRUE(ctx);
    EXPECT_CALL(*ctx, SetContentClip(ClipRectEq(frameNode_->GetGeometryNode()->GetPaddingRect()))).Times(1);
    FlushUITasks();

    paintProperty_->UpdateContentClip({ ContentClipMode::BOUNDARY, nullptr });
    EXPECT_CALL(*ctx, SetContentClip(ClipRectEq(frameNode_->GetGeometryNode()->GetFrameRect()))).Times(1);
    FlushUITasks();
}

/**
 * @tc.name: FadingEdge001
 * @tc.desc: Test FadingEdge property
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, FadingEdge001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set FadingEdge
     * @tc.expected: Would create a overlayNode attach to scroll
     */
    const Dimension fadingEdgeLength = Dimension(10.0f);
    ScrollModelNG model = CreateScroll();
    ScrollableModelNG::SetFadingEdge(true, fadingEdgeLength);
    CreateContent(2000.f);
    CreateScrollDone();
    EXPECT_TRUE(frameNode_->GetOverlayNode());
    EXPECT_TRUE(paintProperty_->GetFadingEdge().value_or(false));
    EXPECT_EQ(paintProperty_->GetFadingEdgeLength().value(), fadingEdgeLength);

    /**
     * @tc.steps: step2. Change FadingEdge to false
     * @tc.expected: There is no fading edge
     */
    ScrollableModelNG::SetFadingEdge(AceType::RawPtr(frameNode_), false, fadingEdgeLength);
    frameNode_->MarkModifyDone();
    FlushUITasks();
    EXPECT_TRUE(frameNode_->GetOverlayNode());
    EXPECT_FALSE(paintProperty_->GetFadingEdge().value_or(false));
}

/**
 * @tc.name: FadingEdge002
 * @tc.desc: Test FadingEdge property
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, FadingEdge002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set FadingEdge
     * @tc.expected: Would create a overlayNode attach to scroll
     */
    const Dimension fadingEdgeLength = Dimension(10.0f);
    ScrollModelNG model = CreateScroll();
    ScrollableModelNG::SetFadingEdge(true, fadingEdgeLength);
    CreateContent(2000.f);
    CreateScrollDone();
    EXPECT_TRUE(frameNode_->GetOverlayNode());

    /**
     * @tc.steps: step2. The scroll at top
     * @tc.expected: Fading bottom
     */
    auto paintMethod = UpdateContentModifier();
    EXPECT_FALSE(paintMethod->isFadingTop_);
    EXPECT_TRUE(paintMethod->isFadingBottom_);

    /**
     * @tc.steps: step3. The scroll at middle
     * @tc.expected: Fading both
     */
    ScrollTo(100.0f);
    paintMethod = UpdateContentModifier();
    EXPECT_TRUE(paintMethod->isFadingTop_);
    EXPECT_TRUE(paintMethod->isFadingBottom_);

    /**
     * @tc.steps: step4. The scroll at bottom
     * @tc.expected: Fading top
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    paintMethod = UpdateContentModifier();
    EXPECT_TRUE(paintMethod->isFadingTop_);
    EXPECT_FALSE(paintMethod->isFadingBottom_);
}

/**
 * @tc.name: SetPaintDirection001
 * @tc.desc: Test ScrollFadeEffect SetPaintDirection
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, SetPaintDirection001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollFadeEffect> scrollFadeEffect = AceType::MakeRefPtr<ScrollFadeEffect>(Color::RED);

    /**
     * @tc.steps: step2. Set scrollFadeEffect fadePainter value
     * @tc.expected: The fadePainter direction return up
     */
    scrollFadeEffect->fadePainter_ = AceType::MakeRefPtr<ScrollFadePainter>();
    scrollFadeEffect->fadePainter_->scaleFactor_ = 1.0f;
    scrollFadeEffect->fadePainter_->SetDirection(OverScrollDirection::UP);
    scrollFadeEffect->SetPaintDirection(Axis::VERTICAL, 3.0f, true);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->GetDirection(), OverScrollDirection::DOWN);
}

/**
 * @tc.name: SetPaintDirection002
 * @tc.desc: Test ScrollFadeEffect SetPaintDirection
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, SetPaintDirection002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollFadeEffect> scrollFadeEffect = AceType::MakeRefPtr<ScrollFadeEffect>(Color::RED);

    /**
     * @tc.steps: step2. Set scrollFadeEffect fadePainter value
     * @tc.expected: The fadePainter direction return up
     */
    scrollFadeEffect->fadePainter_ = AceType::MakeRefPtr<ScrollFadePainter>();
    scrollFadeEffect->fadePainter_->scaleFactor_ = 2.3f;
    scrollFadeEffect->fadePainter_->SetDirection(OverScrollDirection::RIGHT);
    scrollFadeEffect->SetPaintDirection(Axis::HORIZONTAL, -5.0f, true);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->GetDirection(), OverScrollDirection::LEFT);
}

/**
 * @tc.name: SetPaintDirection003
 * @tc.desc: Test ScrollFadeEffect SetPaintDirection
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, SetPaintDirection003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollFadeEffect> scrollFadeEffect = AceType::MakeRefPtr<ScrollFadeEffect>(Color::RED);

    /**
     * @tc.steps: step2. Set scrollFadeEffect fadePainter value
     * @tc.expected: The fadePainter direction return up
     */
    scrollFadeEffect->fadePainter_ = AceType::MakeRefPtr<ScrollFadePainter>();
    scrollFadeEffect->fadePainter_->scaleFactor_ = 2.3f;
    scrollFadeEffect->fadePainter_->SetDirection(OverScrollDirection::LEFT);
    scrollFadeEffect->SetPaintDirection(Axis::HORIZONTAL, 4.0f, true);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->GetDirection(), OverScrollDirection::RIGHT);
}

/**
 * @tc.name: ChangeState_RecedeToIdle
 * @tc.desc: Test ScrollFadeController state change from RECEDE to IDLE
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, ChangeState_RecedeToIdle, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create controller and set RECEDE state
     */
    RefPtr<ScrollFadeController> controller = AceType::MakeRefPtr<ScrollFadeController>();
    controller->state_ = OverScrollState::RECEDE;
    controller->pullDistance_ = 50.0f;

    /**
     * @tc.steps: step2. Trigger state change
     * @tc.expected: State changes to IDLE and pullDistance resets
     */
    controller->ChangeState();
    EXPECT_EQ(controller->state_, OverScrollState::IDLE);
    EXPECT_FLOAT_EQ(controller->pullDistance_, 0.0f);
}

/**
 * @tc.name: ChangeStateDefault
 * @tc.desc: Test ScrollFadeController ChangeState
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, ChangeStateDefault, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollFadeController> controller = AceType::MakeRefPtr<ScrollFadeController>();

    /**
     * @tc.steps: step2. Set state value
     * @tc.expected: The pullDistance value return 0
     */
    int32_t value = 6;
    controller->state_ = static_cast<OverScrollState>(value);
    controller->ChangeState();
    EXPECT_EQ(controller->pullDistance_, 0.0);
}

/**
 * @tc.name: CalculateOverScroll001
 * @tc.desc: Test ScrollFadeEffect CalculateOverScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, CalculateOverScroll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollFadeEffect> scrollFadeEffect = AceType::MakeRefPtr<ScrollFadeEffect>(Color::RED);

    /**
     * @tc.steps: step2. Set currentPositionCallback_ to nullptr
     * set leadingCallback_ and trailingCallback_
     */
    scrollFadeEffect->currentPositionCallback_ = nullptr;
    scrollFadeEffect->leadingCallback_ = []() { return -2.0; };
    scrollFadeEffect->trailingCallback_ = []() { return -8.0; };

    /**
     * @tc.steps: step3. Set oldPostion to 2.0 and isReachMax to false
     * @tc.expected: The result of this function returns 0
     */
    auto result = scrollFadeEffect->CalculateOverScroll(2.0, false);
    EXPECT_EQ(result, 0.0);
}

/**
 * @tc.name: CalculateOverScroll002
 * @tc.desc: Test ScrollFadeEffect CalculateOverScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, CalculateOverScroll002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollFadeEffect> scrollFadeEffect = AceType::MakeRefPtr<ScrollFadeEffect>(Color::RED);

    /**
     * @tc.steps: step2. Set currentPositionCallback_ and leadingCallback_
     * set trailingCallback_ to nullptr
     */
    scrollFadeEffect->currentPositionCallback_ = []() { return -4.0; };
    scrollFadeEffect->leadingCallback_ = []() { return -2.0; };
    scrollFadeEffect->trailingCallback_ = nullptr;

    /**
     * @tc.steps: step3. Set oldPostion to 2.0 and isReachMax to false
     * @tc.expected: The result of this function returns 0
     */
    auto result = scrollFadeEffect->CalculateOverScroll(2.0, false);
    EXPECT_EQ(result, 0.0);
}

/**
 * @tc.name: CalculateOverScroll003
 * @tc.desc: Test ScrollFadeEffect CalculateOverScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, CalculateOverScroll003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollFadeEffect> scrollFadeEffect = AceType::MakeRefPtr<ScrollFadeEffect>(Color::RED);

    /**
     * @tc.steps: step2. Set trailingCallback_ and leadingCallback_ to nullptr
     * set currentPositionCallback_
     */
    scrollFadeEffect->currentPositionCallback_ = []() { return -4.0; };
    scrollFadeEffect->leadingCallback_ = nullptr;
    scrollFadeEffect->trailingCallback_ = nullptr;

    /**
     * @tc.steps: step3. Set oldPostion to 2.0 and isReachMax to false
     * @tc.expected: The result of this function returns 0
     */
    auto result = scrollFadeEffect->CalculateOverScroll(2.0, false);
    EXPECT_EQ(result, 0.0);
}

/**
 * @tc.name: CalculateOverScroll004
 * @tc.desc: Test ScrollFadeEffect CalculateOverScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, CalculateOverScroll004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollFadeEffect> scrollFadeEffect = AceType::MakeRefPtr<ScrollFadeEffect>(Color::RED);

    /**
     * @tc.steps: step2. Set currentPositionCallback_, leadingCallback_ and trailingCallback_
     * set -currentPositionCallback_() less than oldPosition and oldPosition less or equal to -trailingCallback_()
     */
    scrollFadeEffect->currentPositionCallback_ = []() { return -4.0; };
    scrollFadeEffect->leadingCallback_ = []() { return -2.0; };
    scrollFadeEffect->trailingCallback_ = []() { return -8.0; };

    /**
     * @tc.steps: step3. Set oldPostion to 6.0 and isReachMax to true
     * @tc.expected: The result of this function returns -2
     */
    auto result = scrollFadeEffect->CalculateOverScroll(6.0, true);
    EXPECT_EQ(result, -2.0);
}

/**
 * @tc.name: CalculateOverScroll005
 * @tc.desc: Test ScrollFadeEffect CalculateOverScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, CalculateOverScroll005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollFadeEffect> scrollFadeEffect = AceType::MakeRefPtr<ScrollFadeEffect>(Color::RED);

    /**
     * @tc.steps: step2. Set currentPositionCallback_, leadingCallback_ and trailingCallback_
     * set -currentPositionCallback_() greater than oldPosition and oldPosition greater or equal to -leadingCallback_()
     */
    scrollFadeEffect->currentPositionCallback_ = []() { return -7.0; };
    scrollFadeEffect->leadingCallback_ = []() { return -2.0; };
    scrollFadeEffect->trailingCallback_ = []() { return -8.0; };

    /**
     * @tc.steps: step3. Set oldPostion to 6.0 and isReachMax to true
     * @tc.expected: The result of this function returns 1
     */
    auto result = scrollFadeEffect->CalculateOverScroll(6.0, true);
    EXPECT_EQ(result, 1.0);
}

/**
 * @tc.name: CalculateOverScroll006
 * @tc.desc: Test ScrollFadeEffect CalculateOverScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, CalculateOverScroll006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollFadeEffect> scrollFadeEffect = AceType::MakeRefPtr<ScrollFadeEffect>(Color::RED);

    /**
     * @tc.steps: step2. Set currentPositionCallback_, leadingCallback_ and trailingCallback_
     * set -currentPositionCallback_() less than -trailingCallback_() and -trailingCallback_() less than oldPostion
     */
    scrollFadeEffect->currentPositionCallback_ = []() { return -4.0; };
    scrollFadeEffect->leadingCallback_ = []() { return -2.0; };
    scrollFadeEffect->trailingCallback_ = []() { return -8.0; };

    /**
     * @tc.steps: step3. Set oldPostion to 10.0 and isReachMax to true
     * @tc.expected: The result of this function returns 4
     */
    auto result = scrollFadeEffect->CalculateOverScroll(10.0, true);
    EXPECT_EQ(result, 4.0);
}

/**
 * @tc.name: CalculateOverScroll007
 * @tc.desc: Test ScrollFadeEffect CalculateOverScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, CalculateOverScroll007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollFadeEffect> scrollFadeEffect = AceType::MakeRefPtr<ScrollFadeEffect>(Color::RED);

    /**
     * @tc.steps: step2. Set currentPositionCallback_, leadingCallback_ and trailingCallback_
     * set -currentPositionCallback_() greater than oldPostion and oldPostion less than -leadingCallback_()
     */
    scrollFadeEffect->currentPositionCallback_ = []() { return -4.0; };
    scrollFadeEffect->leadingCallback_ = []() { return -10.0; };
    scrollFadeEffect->trailingCallback_ = []() { return -8.0; };

    /**
     * @tc.steps: step3. Set oldPostion to 2.0 and isReachMax to true
     * @tc.expected: The result of this function returns 0
     */
    auto result = scrollFadeEffect->CalculateOverScroll(2.0, true);
    EXPECT_EQ(result, 0.0);
}

/**
 * @tc.name: CalculateOverScroll008
 * @tc.desc: Test ScrollFadeEffect CalculateOverScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, CalculateOverScroll008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollFadeEffect> scrollFadeEffect = AceType::MakeRefPtr<ScrollFadeEffect>(Color::RED);

    /**
     * @tc.steps: step2. Set currentPositionCallback_, leadingCallback_ and trailingCallback_
     * set -currentPositionCallback_() greater than -leadingCallback_() and oldPostion less than -leadingCallback_()
     */
    scrollFadeEffect->currentPositionCallback_ = []() { return -10.0; };
    scrollFadeEffect->leadingCallback_ = []() { return -8.0; };
    scrollFadeEffect->trailingCallback_ = []() { return -2.0; };

    /**
     * @tc.steps: step3. Set oldPostion to 4.0 and isReachMax to true
     * @tc.expected: The result of this function returns 2
     */
    auto result = scrollFadeEffect->CalculateOverScroll(4.0, true);
    EXPECT_EQ(result, 2.0);
}

/**
 * @tc.name: CalculateOverScroll009
 * @tc.desc: Test ScrollFadeEffect CalculateOverScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, CalculateOverScroll009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollFadeEffect> scrollFadeEffect = AceType::MakeRefPtr<ScrollFadeEffect>(Color::RED);

    /**
     * @tc.steps: step2. Set currentPositionCallback_, leadingCallback_ and trailingCallback_
     * set -currentPositionCallback_() greater than -leadingCallback_() and oldPostion less than -leadingCallback_()
     */
    scrollFadeEffect->currentPositionCallback_ = []() { return -10.0; };
    scrollFadeEffect->leadingCallback_ = []() { return -8.0; };
    scrollFadeEffect->trailingCallback_ = []() { return -2.0; };

    /**
     * @tc.steps: step3. Set oldPostion to 4.0 and isReachMax to false
     * @tc.expected: The result of this function returns 0
     */
    auto result = scrollFadeEffect->CalculateOverScroll(4.0, false);
    EXPECT_EQ(result, 0.0);
}

/**
 * @tc.name: CalculateOverScroll010
 * @tc.desc: Test ScrollFadeEffect CalculateOverScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, CalculateOverScroll010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollFadeEffect> scrollFadeEffect = AceType::MakeRefPtr<ScrollFadeEffect>(Color::RED);

    /**
     * @tc.steps: step2. Set currentPositionCallback_, leadingCallback_ and trailingCallback_
     * set -trailingCallback_() greater than oldPostion and -currentPositionCallback_() less than -leadingCallback_()
     */
    scrollFadeEffect->currentPositionCallback_ = []() { return -6.0; };
    scrollFadeEffect->leadingCallback_ = []() { return -4.0; };
    scrollFadeEffect->trailingCallback_ = []() { return -2.0; };

    /**
     * @tc.steps: step3. Set oldPostion to 6.0 and isReachMax to false
     * @tc.expected: The result of this function returns 0
     */
    auto result = scrollFadeEffect->CalculateOverScroll(6.0, false);
    EXPECT_EQ(result, 0.0);
}

/**
 * @tc.name: CalculateOverScroll011
 * @tc.desc: Test ScrollFadeEffect CalculateOverScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, CalculateOverScroll011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollFadeEffect> scrollFadeEffect = AceType::MakeRefPtr<ScrollFadeEffect>(Color::RED);

    /**
     * @tc.steps: step2. Set currentPositionCallback_, leadingCallback_ and trailingCallback_
     * set -trailingCallback_() greater than oldPostion and -currentPositionCallback_() less than -leadingCallback_()
     */
    scrollFadeEffect->currentPositionCallback_ = []() { return -10.0; };
    scrollFadeEffect->leadingCallback_ = []() { return -10.0; };
    scrollFadeEffect->trailingCallback_ = []() { return -10.0; };

    /**
     * @tc.steps: step3. Set oldPostion to 8.0 and isReachMax to false
     * @tc.expected: The result of this function returns 0
     */
    auto result = scrollFadeEffect->CalculateOverScroll(10.0, false);
    EXPECT_EQ(result, 0.0);
}

/**
 * @tc.name: SetPaintDirection004
 * @tc.desc: Test ScrollFadeEffect SetPaintDirection
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, SetPaintDirection004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollFadeEffect> scrollFadeEffect = AceType::MakeRefPtr<ScrollFadeEffect>(Color::RED);
    scrollFadeEffect->fadePainter_ = AceType::MakeRefPtr<ScrollFadePainter>();

    /**
     * @tc.steps: step2. Set scaleFactor_ of fadePainter less than SCALE_THRESHOLD(0.3)
     * and set direction_ of fadePainter to UP
     */
    scrollFadeEffect->fadePainter_->scaleFactor_ = 0.2f;
    scrollFadeEffect->fadePainter_->SetDirection(OverScrollDirection::UP);

    /**
     * @tc.steps: step3. Set axis to VERTICAL, overScroll to 3.0f and isNotPositiveScrollableDistance to true
     * @tc.expected: The direction_ of fadePainter to be DOWN
     */
    scrollFadeEffect->SetPaintDirection(Axis::VERTICAL, 3.0f, true);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->GetDirection(), OverScrollDirection::DOWN);
}

/**
 * @tc.name: SetPaintDirection005
 * @tc.desc: Test ScrollFadeEffect SetPaintDirection
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, SetPaintDirection005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollFadeEffect> scrollFadeEffect = AceType::MakeRefPtr<ScrollFadeEffect>(Color::RED);
    scrollFadeEffect->fadePainter_ = AceType::MakeRefPtr<ScrollFadePainter>();

    /**
     * @tc.steps: step2. Set scaleFactor_ to 0.2f and set direction_ of fadePainter to LEFT
     */
    scrollFadeEffect->fadePainter_->scaleFactor_ = 0.2f;
    scrollFadeEffect->fadePainter_->SetDirection(OverScrollDirection::LEFT);

    /**
     * @tc.steps: step3. Set axis to VERTICAL, overScroll to 3.0f and isNotPositiveScrollableDistance to true
     * @tc.expected: The direction_ of fadePainter to be DOWN
     */
    scrollFadeEffect->SetPaintDirection(Axis::VERTICAL, 3.0f, true);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->GetDirection(), OverScrollDirection::DOWN);
}

/**
 * @tc.name: SetPaintDirection006
 * @tc.desc: Test ScrollFadeEffect SetPaintDirection
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, SetPaintDirection006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollFadeEffect> scrollFadeEffect = AceType::MakeRefPtr<ScrollFadeEffect>(Color::RED);
    scrollFadeEffect->fadePainter_ = AceType::MakeRefPtr<ScrollFadePainter>();

    /**
     * @tc.steps: step2. Set scaleFactor_ of fadePainter less than SCALE_THRESHOLD(0.3)
     * and set direction_ of fadePainter to RIGHT
     */
    scrollFadeEffect->fadePainter_->scaleFactor_ = 0.2f;
    scrollFadeEffect->fadePainter_->SetDirection(OverScrollDirection::RIGHT);

    /**
     * @tc.steps: step3. Set axis to HORIZONTAL, overScroll to 3.0f and isNotPositiveScrollableDistance to true
     * @tc.expected: The direction_ of fadePainter to be LEFT
     */
    scrollFadeEffect->SetPaintDirection(Axis::HORIZONTAL, -3.0f, true);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->GetDirection(), OverScrollDirection::LEFT);
}

/**
 * @tc.name: SetPaintDirection007
 * @tc.desc: Test ScrollFadeEffect SetPaintDirection
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, SetPaintDirection007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollFadeEffect> scrollFadeEffect = AceType::MakeRefPtr<ScrollFadeEffect>(Color::RED);
    scrollFadeEffect->fadePainter_ = AceType::MakeRefPtr<ScrollFadePainter>();

    /**
     * @tc.steps: step2. Set scaleFactor_ to 0.2f and set direction_ of fadePainter to UP
     */
    scrollFadeEffect->fadePainter_->scaleFactor_ = 0.2f;
    scrollFadeEffect->fadePainter_->SetDirection(OverScrollDirection::UP);

    /**
     * @tc.steps: step3. Set axis to HORIZONTAL, overScroll to 3.0f and isNotPositiveScrollableDistance to true
     * @tc.expected: The direction_ of fadePainter to be LEFT
     */
    scrollFadeEffect->SetPaintDirection(Axis::HORIZONTAL, -3.0f, true);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->GetDirection(), OverScrollDirection::LEFT);
}

/**
 * @tc.name: SetPaintDirection008
 * @tc.desc: Test ScrollFadeEffect SetPaintDirection
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, SetPaintDirection008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollFadeEffect> scrollFadeEffect = AceType::MakeRefPtr<ScrollFadeEffect>(Color::RED);
    scrollFadeEffect->fadePainter_ = AceType::MakeRefPtr<ScrollFadePainter>();

    /**
     * @tc.steps: step2. Set scaleFactor_ of fadePainter less than SCALE_THRESHOLD(0.3)
     * and set direction_ of fadePainter to UP
     */
    scrollFadeEffect->fadePainter_->scaleFactor_ = 0.2f;
    scrollFadeEffect->fadePainter_->SetDirection(OverScrollDirection::UP);

    /**
     * @tc.steps: step3. Set axis to HORIZONTAL, overScroll to 3.0f and isNotPositiveScrollableDistance to true
     * @tc.expected: The direction_ of fadePainter to be RIGHT
     */
    scrollFadeEffect->SetPaintDirection(Axis::HORIZONTAL, 3.0f, true);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->GetDirection(), OverScrollDirection::RIGHT);
}

/**
 * @tc.name: SetPaintDirection009
 * @tc.desc: Test ScrollFadeEffect SetPaintDirection
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, SetPaintDirection009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollFadeEffect> scrollFadeEffect = AceType::MakeRefPtr<ScrollFadeEffect>(Color::RED);
    scrollFadeEffect->fadePainter_ = AceType::MakeRefPtr<ScrollFadePainter>();

    /**
     * @tc.steps: step2. Set scaleFactor_ to 0.2f and set direction_ of fadePainter to LEFT
     */
    scrollFadeEffect->fadePainter_->scaleFactor_ = 0.2f;
    scrollFadeEffect->fadePainter_->SetDirection(OverScrollDirection::LEFT);

    /**
     * @tc.steps: step3. Set axis to HORIZONTAL, overScroll to 3.0f and isNotPositiveScrollableDistance to true
     * @tc.expected: The direction_ of fadePainter to be RIGHT
     */
    scrollFadeEffect->SetPaintDirection(Axis::HORIZONTAL, 3.0f, true);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->GetDirection(), OverScrollDirection::RIGHT);
}

/**
 * @tc.name: SetPaintDirection010
 * @tc.desc: Test ScrollFadeEffect SetPaintDirection
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, SetPaintDirection010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollFadeEffect> scrollFadeEffect = AceType::MakeRefPtr<ScrollFadeEffect>(Color::RED);
    scrollFadeEffect->fadePainter_ = AceType::MakeRefPtr<ScrollFadePainter>();

    /**
     * @tc.steps: step2. Set scaleFactor_ of fadePainter less than SCALE_THRESHOLD(0.3)
     * and set direction_ of fadePainter to DOWN
     */
    scrollFadeEffect->fadePainter_->scaleFactor_ = 0.2f;
    scrollFadeEffect->fadePainter_->SetDirection(OverScrollDirection::DOWN);

    /**
     * @tc.steps: step3. Set axis to VERTICAL, overScroll to -3.0f and isNotPositiveScrollableDistance to true
     * @tc.expected: The direction_ of fadePainter to be UP
     */
    scrollFadeEffect->SetPaintDirection(Axis::VERTICAL, -3.0f, true);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->GetDirection(), OverScrollDirection::UP);
}

/**
 * @tc.name: SetPaintDirection011
 * @tc.desc: Test ScrollFadeEffect SetPaintDirection
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, SetPaintDirection011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollFadeEffect> scrollFadeEffect = AceType::MakeRefPtr<ScrollFadeEffect>(Color::RED);
    scrollFadeEffect->fadePainter_ = AceType::MakeRefPtr<ScrollFadePainter>();

    /**
     * @tc.steps: step2. Set scaleFactor_ to 0.2f and set direction_ of fadePainter to LEFT
     */
    scrollFadeEffect->fadePainter_->scaleFactor_ = 0.2f;
    scrollFadeEffect->fadePainter_->SetDirection(OverScrollDirection::LEFT);

    /**
     * @tc.steps: step3. Set axis to VERTICAL, overScroll to -3.0f and isNotPositiveScrollableDistance to true
     * @tc.expected: The direction_ of fadePainter to be DOWN
     */
    scrollFadeEffect->SetPaintDirection(Axis::VERTICAL, -3.0f, true);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->GetDirection(), OverScrollDirection::UP);
}

/**
 * @tc.name: SetPaintDirection012
 * @tc.desc: Test ScrollFadeEffect SetPaintDirection
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, SetPaintDirection012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollFadeEffect> scrollFadeEffect = AceType::MakeRefPtr<ScrollFadeEffect>(Color::RED);
    scrollFadeEffect->fadePainter_ = AceType::MakeRefPtr<ScrollFadePainter>();

    /**
     * @tc.steps: step2. Set scaleFactor_ of fadePainter less than SCALE_THRESHOLD(0.3)
     * and set direction_ of fadePainter to UP
     */
    scrollFadeEffect->fadePainter_->scaleFactor_ = 0.2f;
    scrollFadeEffect->fadePainter_->SetDirection(OverScrollDirection::UP);

    /**
     * @tc.steps: step3. Set axis to HORIZONTAL, overScroll to -3.0f and isNotPositiveScrollableDistance to false
     * @tc.expected: The direction_ of fadePainter to be LEFT
     */
    scrollFadeEffect->SetPaintDirection(Axis::HORIZONTAL, -3.0f, false);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->GetDirection(), OverScrollDirection::LEFT);
}

/**
 * @tc.name: SetPaintDirection013
 * @tc.desc: Test ScrollFadeEffect SetPaintDirection
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, SetPaintDirection013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollFadeEffect> scrollFadeEffect = AceType::MakeRefPtr<ScrollFadeEffect>(Color::RED);
    scrollFadeEffect->fadePainter_ = AceType::MakeRefPtr<ScrollFadePainter>();

    /**
     * @tc.steps: step2. Set scaleFactor_ to 0.2f and set direction_ of fadePainter to LEFT
     */
    scrollFadeEffect->fadePainter_->scaleFactor_ = 0.2f;
    scrollFadeEffect->fadePainter_->SetDirection(OverScrollDirection::LEFT);

    /**
     * @tc.steps: step3. Set axis to HORIZONTAL, overScroll to 3.0f and isNotPositiveScrollableDistance to false
     * @tc.expected: The direction_ of fadePainter to be RIGHT
     */
    scrollFadeEffect->SetPaintDirection(Axis::HORIZONTAL, 3.0f, false);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->GetDirection(), OverScrollDirection::RIGHT);
}

/**
 * @tc.name: SetOpacityAndScale001
 * @tc.desc: Test ScrollFadeEffect SetOpacityAndScale
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, SetOpacityAndScale001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollFadeEffect> scrollFadeEffect = AceType::MakeRefPtr<ScrollFadeEffect>(Color::RED);
    scrollFadeEffect->fadePainter_ = AceType::MakeRefPtr<ScrollFadePainter>();

    /**
     * @tc.steps: step2. Set scaleFactor_ to 0.2f and opacity_ of fadePainter to 1.0f
     */
    scrollFadeEffect->fadePainter_->SetScaleFactor(0.2f);
    scrollFadeEffect->fadePainter_->SetOpacity(1.0f);

    /**
     * @tc.steps: step3. Calling the SetOpacityAndScale function
     * @tc.expected: The scaleFactor_ to be 2.0f and the opacity_ to be 3.0f
     */
    scrollFadeEffect->SetOpacityAndScale(3.0f, 2.0f);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->GetScaleFactor(), 2.0f);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->GetOpacity(), 3.0f);
}

/**
 * @tc.name: SetOpacityAndScale002
 * @tc.desc: Test ScrollFadeEffect SetOpacityAndScale
 * @tc.type: FUNC
 */
HWTEST_F(ScrollEffectTestNg, SetOpacityAndScale002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollFadeEffect> scrollFadeEffect = AceType::MakeRefPtr<ScrollFadeEffect>(Color::RED);
    scrollFadeEffect->fadePainter_ = AceType::MakeRefPtr<ScrollFadePainter>();

    /**
     * @tc.steps: step2. Set scaleFactor_ to 0.2f and opacity_ of fadePainter to 1.0f
     * and set handleOverScroll to false
     */
    scrollFadeEffect->fadePainter_->SetScaleFactor(0.2f);
    scrollFadeEffect->fadePainter_->SetOpacity(1.0f);
    bool handleOverScroll = false;
    scrollFadeEffect->handleOverScrollCallback_ = [&handleOverScroll] { handleOverScroll = true; };

    /**
     * @tc.steps: step3. Calling the SetOpacityAndScale function
     * @tc.expected: The scaleFactor_ to be 2.0f and the opacity_ to be 3.0f
     * the handleOverScroll to be true
     */
    scrollFadeEffect->SetOpacityAndScale(3.0f, 2.0f);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->GetScaleFactor(), 2.0f);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->GetOpacity(), 3.0f);
    EXPECT_EQ(handleOverScroll, true);
}
} // namespace OHOS::Ace::NG
