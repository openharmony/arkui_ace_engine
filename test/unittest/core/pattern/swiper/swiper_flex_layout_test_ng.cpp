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

    void CreateSwiperInFlexLayout();
    RefPtr<FrameNode> parent_ = nullptr;
    RefPtr<FrameNode> leftSibling_ = nullptr;
    RefPtr<FrameNode> rightSibling_ = nullptr;
};

void SwiperFlexLayoutTestNg::CreateSwiperInFlexLayout()
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(1);
    CreateSwiperItems(ITEM_NUM);
    CreateSwiperDone();
    layoutProperty_->UpdateLoop(true);
    layoutProperty_->UpdatePrevMargin(Dimension(MARGIN));
    layoutProperty_->UpdateNextMargin(Dimension(MARGIN));
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
    CreateSwiperInFlexLayout();

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
    CreateSwiperInFlexLayout();

    layoutProperty_->UpdateLoop(false);
    layoutProperty_->UpdatePrevMargin(Dimension(0.0f));
    layoutProperty_->UpdateNextMargin(Dimension(0.0f));
    FlushUITasks();
    EXPECT_EQ(pattern_->itemPosition_.size(), 1);
    EXPECT_EQ(GetChildX(frameNode_, 0), 0.0f);
    EXPECT_EQ(GetChildWidth(frameNode_, 0), 5 * FLEX_WIDTH / 6);

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
    CreateSwiperInFlexLayout();

    layoutProperty_->UpdateLoop(false);
    layoutProperty_->UpdatePrevMargin(Dimension(0.0f));
    layoutProperty_->UpdateNextMargin(Dimension(0.0f));
    FlushUITasks();

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
    CreateSwiperInFlexLayout();

    leftSibling_->layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(0.0f), CalcLength(FLEX_HEIGHT)));
    FlushUITasks();
    FlushUITasks();
    EXPECT_EQ(pattern_->itemPosition_.size(), 2);
    EXPECT_EQ(GetChildX(frameNode_, 0), 10.0f);
    EXPECT_EQ(GetChildWidth(frameNode_, 0), FLEX_WIDTH - 20.0f);
    EXPECT_EQ(GetChildX(frameNode_, 1), FLEX_WIDTH - 10.0f);

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
    CreateSwiperInFlexLayout();

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
    CreateSwiperInFlexLayout();

    layoutProperty_->UpdateLoop(false);
    layoutProperty_->UpdatePrevMargin(Dimension(0.0f));
    layoutProperty_->UpdateNextMargin(Dimension(0.0f));
    FlushUITasks();

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
    CreateSwiperInFlexLayout();

    layoutProperty_->UpdateLoop(false);
    layoutProperty_->UpdatePrevMargin(Dimension(0.0f));
    layoutProperty_->UpdateNextMargin(Dimension(0.0f));
    FlushUITasks();
    controller_->ChangeIndex(1, false);
    FlushUITasks();
    EXPECT_EQ(pattern_->itemPosition_.size(), 1);
    EXPECT_EQ(GetChildX(frameNode_, 1), 0.0f);
    EXPECT_EQ(GetChildWidth(frameNode_, 1), 5 * FLEX_WIDTH / 6);

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
    CreateSwiperInFlexLayout();
    EXPECT_EQ(GetChildX(frameNode_, 0), 10.0f);
    EXPECT_TRUE(NearEqual(GetChildX(frameNode_, 1), 5 * FLEX_WIDTH / 6 - 10.0f));

    controller_->ShowNext();
    EXPECT_TRUE(pattern_->propertyAnimationIsRunning_);
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(pattern_->propertyAnimationIsRunning_);
    auto mainSize = 5 * FLEX_WIDTH / 6 - 20.0f;
    for (int i = 0; i < 2; ++i) {
        auto translate = GetChildFrameNode(frameNode_, i)->GetRenderContext()->GetTranslateXYProperty();
        EXPECT_TRUE(NearEqual(translate, OffsetF(-mainSize / 2, 0.0f)));
    }
    leftSibling_->layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(0.0f), CalcLength(FLEX_HEIGHT)));
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FALSE(pattern_->propertyAnimationIsRunning_);
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 1)->IsActive());
    EXPECT_EQ(GetChildX(frameNode_, 1), 10.0f);
    EXPECT_EQ(pattern_->currentIndex_, 1);
}
} // namespace OHOS::Ace::NG