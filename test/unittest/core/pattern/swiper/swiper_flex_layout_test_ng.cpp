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

#include "core/components_ng/pattern/flex/flex_layout_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "test/mock/core/animation/mock_animation_manager.h"

namespace OHOS::Ace::NG {
namespace {
    static constexpr float FLEX_WIDTH = 500.0f;
    static constexpr float FLEX_WIDTH_NEW = 600.0f;
    static constexpr float FLEX_HEIGHT = 800.0f;
    static constexpr float COLUMN_WIDTH = 100.0f;
    static constexpr float MARGIN = 10.0f;
    static constexpr int32_t ITEM_NUM = 2;
    static constexpr int32_t TICKS = 2;
}

class SwiperFlexLayoutTestNg : public SwiperTestNg {
public:
    static void SetUpTestSuite()
    {
        SwiperTestNg::SetUpTestSuite();
        MockAnimationManager::Enable(true);
        MockAnimationManager::GetInstance().SetTicks(TICKS);
    }

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

    void CreateSwiperInFlexLayout(bool loop = true, int32_t childrenSize = ITEM_NUM,
        int32_t displayCount = 1, float margin = MARGIN);
    RefPtr<FrameNode> parent_ = nullptr;
    RefPtr<FrameNode> leftSibling_ = nullptr;
    RefPtr<FrameNode> rightSibling_ = nullptr;
};

void SwiperFlexLayoutTestNg::CreateSwiperInFlexLayout(
    bool loop, int32_t childrenSize, int32_t displayCount, float margin)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(displayCount);
    CreateSwiperItems(childrenSize);
    CreateSwiperDone();
    layoutProperty_->UpdateLoop(loop);
    layoutProperty_->UpdatePrevMargin(Dimension(margin));
    layoutProperty_->UpdateNextMargin(Dimension(margin));
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(FLEX_WIDTH), CalcLength(FLEX_HEIGHT)));

    // flex parent node
    parent_ = FrameNode::CreateFrameNode("Flex", -1, AceType::MakeRefPtr<FlexLayoutPattern>());
    parent_->layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(FLEX_WIDTH), CalcLength(FLEX_HEIGHT)));
    parent_->GetLayoutProperty<FlexLayoutProperty>()->UpdateFlexDirection(FlexDirection::ROW);

    // sibling node
    leftSibling_ = FrameNode::CreateFrameNode("sibling", -1, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    leftSibling_->layoutProperty_->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(COLUMN_WIDTH), CalcLength(FLEX_HEIGHT)));
    leftSibling_->MountToParent(parent_);

    // mount swiper
    frameNode_->MountToParent(parent_);

    // sibling node
    rightSibling_ = FrameNode::CreateFrameNode("sibling", -1, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    rightSibling_->layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(0.0f), CalcLength(FLEX_HEIGHT)));
    rightSibling_->MountToParent(parent_);
    parent_->MarkModifyDone();
    CreateLayoutTask(parent_);
}

/**
 * @tc.name: SwiperFlexLayoutBase001
 * @tc.desc: Test swiper with flex parent and layout.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperFlexLayoutTestNg, SwiperFlexLayoutBase001, TestSize.Level1)
{
    CreateSwiperInFlexLayout();
    EXPECT_EQ(pattern_->itemPosition_.size(), 2);

    EXPECT_EQ(GetChildX(parent_, 0), 0.0f);
    EXPECT_TRUE(NearEqual(GetChildX(parent_, 1), FLEX_WIDTH / 6));
    EXPECT_EQ(GetChildX(parent_, 2), FLEX_WIDTH);

    EXPECT_EQ(GetChildX(frameNode_, 0), 10.0f);
    EXPECT_TRUE(NearEqual(GetChildX(frameNode_, 1), 5 * FLEX_WIDTH / 6 - 10.0f));
}

/**
 * @tc.name: SwiperFlexLayout001
 * @tc.desc: Test drag for swiper in flex.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperFlexLayoutTestNg, SwiperFlexLayout001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper with sibling inside flex layout
     */
    CreateSwiperInFlexLayout();

    /**
     * @tc.steps: step2. Simulate drag update
     * @tc.expected: Swiper offset will not jump to zero after second flush task.
     */
    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();
    EXPECT_EQ(GetChildX(frameNode_, 0), -90.0f);
    FlushUITasks();
    EXPECT_EQ(GetChildX(frameNode_, 0), -90.0f);
}

/**
 * @tc.name: SwiperFlexLayout002
 * @tc.desc: Test spring animation for swiper in flex.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperFlexLayoutTestNg, SwiperFlexLayout002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper with sibling inside flex layout
     */
    CreateSwiperInFlexLayout();
    layoutProperty_->UpdateLoop(false);
    layoutProperty_->UpdatePrevMargin(Dimension(0.0f));
    layoutProperty_->UpdateNextMargin(Dimension(0.0f));
    FlushUITasks();
    EXPECT_EQ(pattern_->itemPosition_.size(), 1);
    EXPECT_EQ(GetChildX(frameNode_, 0), 0.0f);
    EXPECT_EQ(GetChildWidth(frameNode_, 0), 5 * FLEX_WIDTH / 6);

    /**
     * @tc.steps: step2. Simulate swipe to to right, test for spring animation
     * @tc.expected: Spring animation runs properly and finished after second tick.
     */
    SimulateSwipe(200.0f, 200.0f);
    FlushUITasks();
    auto visibleSize = pattern_->CalculateVisibleSize();
    ASSERT_TRUE(visibleSize > 0.0f);
    auto realOffset = 200.0f * SwiperHelper::CalculateFriction(200.0f / visibleSize);
    EXPECT_TRUE(NearEqual(GetChildX(frameNode_, 0), realOffset));
    EXPECT_TRUE(pattern_->springAnimationIsRunning_);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_TRUE(NearEqual(GetChildX(frameNode_, 0), realOffset / 2));

    // check offset after spring animation finished
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(pattern_->springAnimationIsRunning_);
    FlushUITasks();
    EXPECT_TRUE(NearEqual(GetChildX(frameNode_, 0), 0.0f));
}

/**
 * @tc.name: SwiperFlexLayout003
 * @tc.desc: Test showNext & showPrevious in flex layout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperFlexLayoutTestNg, SwiperFlexLayout003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper with sibling inside flex layout
     */
    CreateSwiperInFlexLayout();
    layoutProperty_->UpdateLoop(false);
    layoutProperty_->UpdatePrevMargin(Dimension(0.0f));
    layoutProperty_->UpdateNextMargin(Dimension(0.0f));
    FlushUITasks();

    /**
     * @tc.steps: step2. Test showNext translate animation in flex layout
     * @tc.expected: Translate animation runs properly and finished after second tick.
     */
    controller_->ShowNext();
    EXPECT_TRUE(pattern_->propertyAnimationIsRunning_);
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(pattern_->propertyAnimationIsRunning_);
    auto mainSize = 5 * FLEX_WIDTH / 6;
    for (int i = 0; i < 2; ++i) {
        auto translate = GetChildFrameNode(frameNode_, i)->GetRenderContext()->GetTranslateXYProperty();
        EXPECT_TRUE(NearEqual(translate, OffsetF(-mainSize / 2, 0.0f)));
    }
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(pattern_->propertyAnimationIsRunning_);

    EXPECT_TRUE(GetChildFrameNode(frameNode_, 1)->IsActive());
    EXPECT_EQ(GetChildX(frameNode_, 1), 0);
    EXPECT_EQ(pattern_->currentIndex_, 1);

    /**
     * @tc.steps: step3. Test showPrevious translate animation in flex layout
     * @tc.expected: Translate animation runs properly and finished after second tick.
     */
    controller_->ShowPrevious();
    EXPECT_TRUE(pattern_->propertyAnimationIsRunning_);
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(pattern_->propertyAnimationIsRunning_);
    for (int i = 0; i < 2; ++i) {
        auto translate = GetChildFrameNode(frameNode_, i)->GetRenderContext()->GetTranslateXYProperty();
        EXPECT_TRUE(NearEqual(translate, OffsetF(mainSize / 2, 0.0f)));
    }
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(pattern_->propertyAnimationIsRunning_);
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 0)->IsActive());
    EXPECT_EQ(GetChildX(frameNode_, 0), 0);
    EXPECT_EQ(pattern_->currentIndex_, 0);
}

/**
 * @tc.name: SwiperFlexLayout004
 * @tc.desc: Test flex layout when layout constraint changed.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperFlexLayoutTestNg, SwiperFlexLayout004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper with sibling inside flex layout
     */
    CreateSwiperInFlexLayout();

    /**
     * @tc.steps: step2. Change left sibling's width to zero
     */
    leftSibling_->layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(0.0f), CalcLength(FLEX_HEIGHT)));
    FlushUITasks();
    FlushUITasks();
    EXPECT_EQ(pattern_->itemPosition_.size(), 2);
    EXPECT_EQ(GetChildX(frameNode_, 0), 10.0f);
    EXPECT_EQ(GetChildWidth(frameNode_, 0), FLEX_WIDTH - 20.0f);
    EXPECT_EQ(GetChildX(frameNode_, 1), FLEX_WIDTH - 10.0f);

    /**
     * @tc.steps: step3. Change left sibling's width to 100
     * @tc.expected: Width of swiper item changes proportionally
     */
    leftSibling_->layoutProperty_->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(COLUMN_WIDTH), CalcLength(FLEX_HEIGHT)));
    FlushUITasks();
    FlushUITasks();
    EXPECT_EQ(pattern_->itemPosition_.size(), 2);
    EXPECT_EQ(GetChildX(frameNode_, 0), 10.0f);
    EXPECT_EQ(GetChildWidth(frameNode_, 0), 5 * FLEX_WIDTH / 6 - 20.0f);
    EXPECT_EQ(GetChildX(frameNode_, 1), 5 * FLEX_WIDTH / 6 - 10.0f);
}

/**
 * @tc.name: SwiperFlexLayout005
 * @tc.desc: Test flex layout when parent's layout constraint changed.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperFlexLayoutTestNg, SwiperFlexLayout005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper with sibling inside flex layout
     */
    CreateSwiperInFlexLayout();

    /**
     * @tc.steps: step2. Change parent's layout constraint
     * @tc.expected: No extra offset in swiper's layout.
     */
    parent_->layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(FLEX_WIDTH_NEW), CalcLength(FLEX_HEIGHT)));
    FlushUITasks();
    EXPECT_EQ(pattern_->itemPosition_.size(), 2);
    EXPECT_EQ(GetChildX(frameNode_, 0), 10.0f);
    EXPECT_EQ(GetChildWidth(frameNode_, 0), 5 * FLEX_WIDTH_NEW / 6 - 20.0f);
    EXPECT_EQ(GetChildX(frameNode_, 1), 5 * FLEX_WIDTH_NEW / 6 - 10.0f);
}

/**
 * @tc.name: SwiperFlexLayout006
 * @tc.desc: Change layout constraint during spring animation in flex.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperFlexLayoutTestNg, SwiperFlexLayout006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper with sibling inside flex layout
     */
    CreateSwiperInFlexLayout();
    layoutProperty_->UpdateLoop(false);
    layoutProperty_->UpdatePrevMargin(Dimension(0.0f));
    layoutProperty_->UpdateNextMargin(Dimension(0.0f));
    FlushUITasks();

    /**
     * @tc.steps: step2. Simulate swipe to to right
     * @tc.expected: Running spring animation
     */
    SimulateSwipe(200.0f, 200.0f);
    FlushUITasks();
    auto visibleSize = pattern_->CalculateVisibleSize();
    ASSERT_TRUE(visibleSize > 0.0f);
    auto realOffset = 200.0f * SwiperHelper::CalculateFriction(200.0f / visibleSize);
    EXPECT_TRUE(NearEqual(GetChildX(frameNode_, 0), realOffset));
    EXPECT_TRUE(pattern_->springAnimationIsRunning_);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_TRUE(NearEqual(GetChildX(frameNode_, 0), realOffset / 2));

    /**
     * @tc.steps: step3. Change left sibling's width to zero
     * @tc.expected: Swiper's layout constraint is changed and spring animation is finished immediately.
     */
    leftSibling_->layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(0.0f), CalcLength(FLEX_HEIGHT)));
    FlushUITasks();
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FALSE(pattern_->springAnimationIsRunning_);
    EXPECT_EQ(pattern_->itemPosition_.size(), 1);
    EXPECT_EQ(GetChildX(frameNode_, 0), 0.0f);
    EXPECT_EQ(GetChildWidth(frameNode_, 0), FLEX_WIDTH);
}

/**
 * @tc.name: SwiperFlexLayout007
 * @tc.desc: Change layout constraint during spring animation in flex.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperFlexLayoutTestNg, SwiperFlexLayout007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper with sibling inside flex layout
     */
    CreateSwiperInFlexLayout();
    layoutProperty_->UpdateLoop(false);
    layoutProperty_->UpdatePrevMargin(Dimension(0.0f));
    layoutProperty_->UpdateNextMargin(Dimension(0.0f));
    FlushUITasks();

    /**
     * @tc.steps: step2. Change index to 1 and check itemPosition
     */
    controller_->ChangeIndex(1, false);
    FlushUITasks();
    EXPECT_EQ(pattern_->itemPosition_.size(), 1);
    EXPECT_EQ(GetChildX(frameNode_, 1), 0.0f);
    EXPECT_EQ(GetChildWidth(frameNode_, 1), 5 * FLEX_WIDTH / 6);

    /**
     * @tc.steps: step3. Simulate swipe to to left
     * @tc.expected: Running spring animation
     */
    SimulateSwipe(-200.0f, -200.0f);
    FlushUITasks();
    auto visibleSize = pattern_->CalculateVisibleSize();
    ASSERT_TRUE(visibleSize > 0.0f);
    auto realOffset = -200.0f * SwiperHelper::CalculateFriction(200.0f / visibleSize);
    EXPECT_TRUE(NearEqual(GetChildX(frameNode_, 1), realOffset));
    EXPECT_TRUE(pattern_->springAnimationIsRunning_);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_TRUE(NearEqual(GetChildX(frameNode_, 1), realOffset / 2));

    /**
     * @tc.steps: step4. Change left sibling's width to zero
     * @tc.expected: Swiper's layout constraint is changed and spring animation is finished immediately.
     */
    leftSibling_->layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(0.0f), CalcLength(FLEX_HEIGHT)));
    FlushUITasks();
    // check offset after spring animation finished
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FALSE(pattern_->springAnimationIsRunning_);
    EXPECT_EQ(pattern_->itemPosition_.size(), 1);
    EXPECT_EQ(GetChildX(frameNode_, 1), 0.0f);
    EXPECT_EQ(GetChildWidth(frameNode_, 1), FLEX_WIDTH);
}

/**
 * @tc.name: SwiperFlexLayout008
 * @tc.desc: Change layout constraint during property translate animation.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperFlexLayoutTestNg, SwiperFlexLayout008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper with sibling inside flex layout
     */
    CreateSwiperInFlexLayout();
    EXPECT_EQ(GetChildX(frameNode_, 0), 10.0f);
    EXPECT_TRUE(NearEqual(GetChildX(frameNode_, 1), 5 * FLEX_WIDTH / 6 - 10.0f));

    /**
     * @tc.steps: step2. Start translate animation using showNext
     * @tc.expected: Running animation
     */
    controller_->ShowNext();
    EXPECT_TRUE(pattern_->propertyAnimationIsRunning_);
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(pattern_->propertyAnimationIsRunning_);
    auto mainSize = 5 * FLEX_WIDTH / 6 - 20.0f;
    for (int i = 0; i < 2; ++i) {
        auto translate = GetChildFrameNode(frameNode_, i)->GetRenderContext()->GetTranslateXYProperty();
        EXPECT_TRUE(NearEqual(translate, OffsetF(-mainSize / 2, 0.0f)));
    }

    /**
     * @tc.steps: step3. Change right sibling's width to zero
     * @tc.expected: Swiper's layout constraint is changed and translate animation is finished immediately.
     */
    leftSibling_->layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(0.0f), CalcLength(FLEX_HEIGHT)));
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FALSE(pattern_->propertyAnimationIsRunning_);
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 1)->IsActive());
    EXPECT_EQ(GetChildX(frameNode_, 1), 10.0f);
    EXPECT_EQ(pattern_->currentIndex_, 1);
}

/**
 * @tc.name: SwiperFlexLayout009
 * @tc.desc: Test OnChange callback in flex layout.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperFlexLayoutTestNg, SwiperFlexLayout009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper with sibling inside flex layout
     */
    const bool loop = true;
    const int32_t childrenSize = 6;
    const int32_t displayCount = 3;
    const float margin = 0.0f;
    CreateSwiperInFlexLayout(loop, childrenSize, displayCount, margin);

    /**
     * @tc.steps: step2. check initial currentIndex
     * @tc.expected: Initial index is zero and swiper is properly layout in flex
     */
    EXPECT_EQ(pattern_->currentIndex_, 0);
    EXPECT_EQ(GetChildX(frameNode_, 0), 0.0f);
    EXPECT_TRUE(NearEqual(GetChildX(frameNode_, 1), 5 * FLEX_WIDTH / (6 * displayCount)));

    /**
     * @tc.steps: step3. Change to index 4 using swiper controller.
     * @tc.expected: OnChange callback is triggered as expexted.
     */
    int32_t currentIndex = 0;
    pattern_->UpdateChangeEvent([&currentIndex](int32_t index) {
        currentIndex = index;
    });
    controller_->ChangeIndex(4, false);
    FlushUITasks();
    EXPECT_EQ(pattern_->currentIndex_, 4);
    EXPECT_TRUE(NearEqual(GetChildX(frameNode_, 0), 2 * 5 * FLEX_WIDTH / (6 * displayCount)));
    EXPECT_EQ(currentIndex, 4);

    /**
     * @tc.steps: step4. Update loop attribute from true to false
     * @tc.expected: Current index changed to 3 and OnChange callback is triggered
     */
    layoutProperty_->UpdateLoop(false);
    pattern_->OnModifyDone();
    FlushUITasks();
    EXPECT_EQ(pattern_->currentIndex_, 3);
    EXPECT_EQ(currentIndex, 3);
}

/**
 * @tc.name: SwiperFlexLayout010
 * @tc.desc: Test prevMargin/nextMargin display status when swiper mainSize changed.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperFlexLayoutTestNg, SwiperFlexLayout010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper with sibling inside flex layout
     */
    const bool loop = true;
    const int32_t childrenSize = 7;
    const int32_t displayCount = 3;
    const float margin = 90.0f;
    CreateSwiperInFlexLayout(loop, childrenSize, displayCount, margin);

    /**
     * @tc.steps: step2. margin is 90.0f, check display status
     * @tc.expected: Do not display prevMargin/nextMargin, because margin is larger than swiper item.
     */
    EXPECT_EQ(layoutProperty_->GetCalculatedPrevMargin(), 0.0f);
    EXPECT_EQ(layoutProperty_->GetCalculatedNextMargin(), 0.0f);
    EXPECT_EQ(GetChildX(frameNode_, 0), 0.0f);
    EXPECT_TRUE(NearEqual(GetChildX(frameNode_, 1), 5 * FLEX_WIDTH / (6 * displayCount)));

    /**
     * @tc.steps: step3. reduce left sibling's width to zero
     * @tc.expected: Display prevMargin/nextMargin, because margin is smaller than swiper item.
     */
    leftSibling_->layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(0.0f), CalcLength(FLEX_HEIGHT)));
    FlushUITasks();
    EXPECT_EQ(layoutProperty_->GetCalculatedPrevMargin(), margin);
    EXPECT_EQ(layoutProperty_->GetCalculatedNextMargin(), margin);
    EXPECT_EQ(GetChildX(frameNode_, 0), margin);
    EXPECT_TRUE(NearEqual(GetChildX(frameNode_, 1), margin + (FLEX_WIDTH - 2 * margin) / displayCount));

    /**
     * @tc.steps: step4. increase right sibling's width to 100
     * @tc.expected: Do not display prevMargin/nextMargin, because margin is larger than swiper item.
     */
    rightSibling_->layoutProperty_->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(COLUMN_WIDTH), CalcLength(FLEX_HEIGHT)));
    FlushUITasks();
    EXPECT_EQ(layoutProperty_->GetCalculatedPrevMargin(), 0.0f);
    EXPECT_EQ(layoutProperty_->GetCalculatedNextMargin(), 0.0f);
    EXPECT_EQ(GetChildX(frameNode_, 0), 0.0f);
    EXPECT_TRUE(NearEqual(GetChildX(frameNode_, 1), 5 * FLEX_WIDTH / (6 * displayCount)));
}
} // namespace OHOS::Ace::NG
