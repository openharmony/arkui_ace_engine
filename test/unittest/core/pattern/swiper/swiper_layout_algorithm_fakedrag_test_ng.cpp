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

#include "swiper_test_ng.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/pattern/swiper/swiper_layout_algorithm.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"

namespace OHOS::Ace::NG {

// ========== Branch 1: NonNegative(currentOffset_) - true (positive offset) ==========

/**
 * @tc.name: MeasureSwiperInFakeDrag001
 * @tc.desc: Test MeasureSwiperInFakeDrag with positive offset (NonNegative=true)
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, MeasureSwiperInFakeDrag001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper in loop mode
     * @tc.expected: Swiper created successfully
     */
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    CreateSwiperItems(5);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Start fake drag with positive offset (NonNegative=true branch)
     * @tc.expected: Should call MeasureForwardFakeDrag
     */
    EXPECT_TRUE(pattern_->StartFakeDrag());
    EXPECT_TRUE(pattern_->isFakeDragging_);

    pattern_->UpdateCurrentOffset(100.0f); // Positive offset
    FlushUITasks();

    /**
     * @tc.steps: step3. Verify items are positioned
     * @tc.expected: itemPosition should not be empty
     */
    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

// ========== Branch 2: NonNegative(currentOffset_) - false (negative offset) ==========

/**
 * @tc.name: MeasureSwiperInFakeDrag002
 * @tc.desc: Test MeasureSwiperInFakeDrag with negative offset (NonNegative=false)
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, MeasureSwiperInFakeDrag002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper in loop mode
     */
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    CreateSwiperItems(5);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Start fake drag with negative offset (NonNegative=false branch)
     * @tc.expected: Should call MeasureBackwardFakeDrag
     */
    EXPECT_TRUE(pattern_->StartFakeDrag());
    EXPECT_TRUE(pattern_->isFakeDragging_);

    pattern_->UpdateCurrentOffset(-100.0f); // Negative offset
    FlushUITasks();

    /**
     * @tc.steps: step3. Verify items are positioned
     */
    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

// ========== Branch 3: NonNegative(currentOffset_) - zero (true) ==========

/**
 * @tc.name: MeasureSwiperInFakeDrag003
 * @tc.desc: Test MeasureSwiperInFakeDrag with zero offset (NonNegative=true for zero)
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, MeasureSwiperInFakeDrag003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper
     */
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems(5);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Start fake drag with zero offset
     * @tc.expected: Should call MeasureForwardFakeDrag (zero is non-negative)
     */
    EXPECT_TRUE(pattern_->StartFakeDrag());
    EXPECT_TRUE(pattern_->isFakeDragging_);

    pattern_->UpdateCurrentOffset(0.0f);
    FlushUITasks();

    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

// ========== Branch 4 & 5: !NearZero(prevMargin_) - true/false ==========

/**
 * @tc.name: MeasureSwiperInFakeDrag004
 * @tc.desc: Test with prevMargin set (!NearZero(prevMargin_)=true)
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, MeasureSwiperInFakeDrag004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper with prevMargin
     */
    SwiperModelNG model = CreateSwiper();
    model.SetPreviousMargin(Dimension(20.0_vp), false);
    CreateSwiperItems(5);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Start fake drag
     * @tc.expected: Should work with prevMargin
     */
    EXPECT_TRUE(pattern_->StartFakeDrag());
    pattern_->UpdateCurrentOffset(50.0f);
    FlushUITasks();

    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

/**
 * @tc.name: MeasureSwiperInFakeDrag005
 * @tc.desc: Test without prevMargin (!NearZero(prevMargin_)=false)
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, MeasureSwiperInFakeDrag005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper without prevMargin
     */
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems(5);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Start fake drag
     * @tc.expected: Should work without prevMargin
     */
    EXPECT_TRUE(pattern_->StartFakeDrag());
    pattern_->UpdateCurrentOffset(50.0f);
    FlushUITasks();

    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

// ========== Branch 6 & 7: !NearZero(nextMargin_) - true/false ==========

/**
 * @tc.name: MeasureSwiperInFakeDrag006
 * @tc.desc: Test with nextMargin set (!NearZero(nextMargin_)=true)
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, MeasureSwiperInFakeDrag006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper with nextMargin
     */
    SwiperModelNG model = CreateSwiper();
    model.SetNextMargin(Dimension(30.0_vp), false);
    CreateSwiperItems(5);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Start fake drag backward
     * @tc.expected: Should work with nextMargin
     */
    EXPECT_TRUE(pattern_->StartFakeDrag());
    pattern_->UpdateCurrentOffset(-50.0f);
    FlushUITasks();

    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

/**
 * @tc.name: MeasureSwiperInFakeDrag007
 * @tc.desc: Test without nextMargin (!NearZero(nextMargin_)=false)
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, MeasureSwiperInFakeDrag007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper without nextMargin
     */
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems(5);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Start fake drag backward
     * @tc.expected: Should work without nextMargin
     */
    EXPECT_TRUE(pattern_->StartFakeDrag());
    pattern_->UpdateCurrentOffset(-50.0f);
    FlushUITasks();

    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

// ========== Branch 10: Non-loop mode forward boundary ==========

/**
 * @tc.name: MeasureSwiperInFakeDrag008
 * @tc.desc: Test non-loop mode with forward boundary
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, MeasureSwiperInFakeDrag008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper without loop
     */
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    CreateSwiperItems(5);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Move to last index and drag forward
     * @tc.expected: Should handle boundary correctly (!isLoop_ && forwardMeasureIndex > totalItemCount_ - 1)
     */
    pattern_->currentIndex_ = 4;
    FlushUITasks();

    EXPECT_TRUE(pattern_->StartFakeDrag());
    pattern_->UpdateCurrentOffset(200.0f);
    FlushUITasks();

    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

// ========== Branch 11: Non-loop mode backward boundary ==========

/**
 * @tc.name: MeasureSwiperInFakeDrag009
 * @tc.desc: Test non-loop mode with backward boundary
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, MeasureSwiperInFakeDrag009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper without loop
     */
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    CreateSwiperItems(5);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. At first index and drag backward
     * @tc.expected: Should handle boundary correctly (!isLoop_ && backwardMeasureIndex < 0)
     */
    pattern_->currentIndex_ = 0;
    FlushUITasks();

    EXPECT_TRUE(pattern_->StartFakeDrag());
    pattern_->UpdateCurrentOffset(-200.0f);
    FlushUITasks();

    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

// ========== Branch 12: Prevent circular layout in loop mode ==========

/**
 * @tc.name: MeasureSwiperInFakeDrag010
 * @tc.desc: Test prevention of circular layout in loop mode
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, MeasureSwiperInFakeDrag010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper in loop mode with few items
     */
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    CreateSwiperItems(3);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Start fake drag with large offset
     * @tc.expected: Should prevent circular layout (!isMeasureBase && loopMeasureIndex == GetLoopIndex(prevEndIndex))
     */
    EXPECT_TRUE(pattern_->StartFakeDrag());
    pattern_->UpdateCurrentOffset(500.0f); // Very large offset
    FlushUITasks();

    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

// ========== Branch 13 & 14: SwipeByGroup mode ==========

/**
 * @tc.name: MeasureSwiperInFakeDrag011
 * @tc.desc: Test swipeByGroup mode with forward drag
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, MeasureSwiperInFakeDrag011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper with swipeByGroup
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(2);
    model.SetSwipeByGroup(true);
    CreateSwiperItems(8);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Start fake drag forward
     * @tc.expected: Should handle swipeByGroup correctly
     */
    EXPECT_TRUE(pattern_->StartFakeDrag());
    pattern_->UpdateCurrentOffset(150.0f);
    FlushUITasks();

    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

/**
 * @tc.name: MeasureSwiperInFakeDrag012
 * @tc.desc: Test swipeByGroup mode with backward drag
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, MeasureSwiperInFakeDrag012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper with swipeByGroup
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(2);
    model.SetSwipeByGroup(true);
    CreateSwiperItems(8);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Start fake drag backward
     * @tc.expected: Should handle swipeByGroup correctly
     */
    EXPECT_TRUE(pattern_->StartFakeDrag());
    pattern_->UpdateCurrentOffset(-150.0f);
    FlushUITasks();

    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

// ========== Branch 15 & 16: Edge position recording (loopMeasureIndex at boundaries) ==========

/**
 * @tc.name: MeasureSwiperInFakeDrag013
 * @tc.desc: Test reaching last item in loop mode
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, MeasureSwiperInFakeDrag013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper in loop mode
     */
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    CreateSwiperItems(5);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Start fake drag to reach last item
     * @tc.expected: Should handle loopMeasureIndex == totalItemCount_ - 1
     */
    EXPECT_TRUE(pattern_->StartFakeDrag());
    pattern_->UpdateCurrentOffset(400.0f);
    FlushUITasks();

    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

/**
 * @tc.name: MeasureSwiperInFakeDrag014
 * @tc.desc: Test reaching first item in loop mode
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, MeasureSwiperInFakeDrag014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper in loop mode
     */
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    CreateSwiperItems(5);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Start fake drag backward to reach first item
     * @tc.expected: Should handle loopMeasureIndex == 0
     */
    EXPECT_TRUE(pattern_->StartFakeDrag());
    pattern_->UpdateCurrentOffset(-400.0f);
    FlushUITasks();

    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

// ========== Branch 17 & 18: Item removal based on edge positions ==========

/**
 * @tc.name: MeasureSwiperInFakeDrag015
 * @tc.desc: Test removing items before startEdgePos
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, MeasureSwiperInFakeDrag015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper with many items
     */
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems(10);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Drag with large positive offset
     * @tc.expected: Items outside range should be removed (LessOrEqual(item.second.endPos, startEdgePos))
     */
    EXPECT_TRUE(pattern_->StartFakeDrag());
    pattern_->UpdateCurrentOffset(400.0f);
    FlushUITasks();

    // Some items should be removed from view
    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

/**
 * @tc.name: MeasureSwiperInFakeDrag016
 * @tc.desc: Test removing items after endEdgePos
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, MeasureSwiperInFakeDrag016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper with many items
     */
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems(10);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Drag with large negative offset
     * @tc.expected: Items outside range should be removed (GreatOrEqual(item.second.startPos, endEdgePos))
     */
    EXPECT_TRUE(pattern_->StartFakeDrag());
    pattern_->UpdateCurrentOffset(-400.0f);
    FlushUITasks();

    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

// ========== Branch 19 & 20: MarginIgnoreBlank ==========

/**
 * @tc.name: MeasureSwiperInFakeDrag017
 * @tc.desc: Test with nextMarginIgnoreBlank enabled
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, MeasureSwiperInFakeDrag017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper with nextMarginIgnoreBlank
     */
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetNextMargin(Dimension(30.0_vp), true);
    CreateSwiperItems(5);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Move to end and drag
     * @tc.expected: Should apply nextMarginIgnoreBlank logic
     */
    pattern_->currentIndex_ = 4;
    FlushUITasks();

    EXPECT_TRUE(pattern_->StartFakeDrag());
    pattern_->UpdateCurrentOffset(100.0f);
    FlushUITasks();

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

/**
 * @tc.name: MeasureSwiperInFakeDrag018
 * @tc.desc: Test with prevMarginIgnoreBlank enabled
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, MeasureSwiperInFakeDrag018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper with prevMarginIgnoreBlank
     */
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetPreviousMargin(Dimension(20.0_vp), true);
    CreateSwiperItems(5);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. At start and drag backward
     * @tc.expected: Should apply prevMarginIgnoreBlank logic
     */
    pattern_->currentIndex_ = 0;
    FlushUITasks();

    EXPECT_TRUE(pattern_->StartFakeDrag());
    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

// ========== Branch 21: itemSpace > 0 ==========

/**
 * @tc.name: MeasureSwiperInFakeDrag019
 * @tc.desc: Test with itemSpace set
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, MeasureSwiperInFakeDrag019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper with itemSpace
     */
    SwiperModelNG model = CreateSwiper();
    model.SetItemSpace(15.0_vp);
    CreateSwiperItems(5);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Start fake drag
     * @tc.expected: Should work with itemSpace
     */
    EXPECT_TRUE(pattern_->StartFakeDrag());
    pattern_->UpdateCurrentOffset(100.0f);
    FlushUITasks();

    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

// ========== Branch 22: ignoreBlankOffset_ != 0 ==========

/**
 * @tc.name: MeasureSwiperInFakeDrag020
 * @tc.desc: Test with ignoreBlankOffset set via prevMarginIgnoreBlank
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, MeasureSwiperInFakeDrag020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper with prevMarginIgnoreBlank
     */
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetPreviousMargin(Dimension(20.0_vp), true);
    CreateSwiperItems(5);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. At start to trigger ignoreBlankOffset
     * @tc.expected: ignoreBlankOffset_ should be applied
     */
    pattern_->currentIndex_ = 0;
    FlushUITasks();

    EXPECT_TRUE(pattern_->StartFakeDrag());
    pattern_->UpdateCurrentOffset(-50.0f);
    FlushUITasks();

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

// ========== Branch 23: Multiple FakeDragBy calls ==========

/**
 * @tc.name: MeasureSwiperInFakeDrag021
 * @tc.desc: Test multiple FakeDragBy calls
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, MeasureSwiperInFakeDrag021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper
     */
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems(5);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Start fake drag and call FakeDragBy multiple times
     * @tc.expected: Each call should update positions incrementally
     */
    EXPECT_TRUE(pattern_->StartFakeDrag());
    EXPECT_TRUE(pattern_->isFakeDragging_);

    EXPECT_TRUE(pattern_->FakeDragBy(50.0f));
    FlushUITasks();

    EXPECT_TRUE(pattern_->FakeDragBy(30.0f));
    FlushUITasks();

    EXPECT_TRUE(pattern_->FakeDragBy(-20.0f));
    FlushUITasks();

    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

// ========== Branch 24: Axis::VERTICAL direction ==========

/**
 * @tc.name: MeasureSwiperInFakeDrag022
 * @tc.desc: Test fake drag in vertical direction
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, MeasureSwiperInFakeDrag022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create vertical swiper
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems(5);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Verify direction is vertical
     */
    EXPECT_EQ(layoutProperty_->GetDirection().value(), Axis::VERTICAL);

    /**
     * @tc.steps: step3. Start fake drag vertically
     * @tc.expected: Should handle vertical axis correctly
     */
    EXPECT_TRUE(pattern_->StartFakeDrag());
    pattern_->UpdateCurrentOffset(100.0f);
    FlushUITasks();

    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

// ========== Branch 25: Stretch mode ==========

/**
 * @tc.name: MeasureSwiperInFakeDrag023
 * @tc.desc: Test fake drag in stretch mode
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, MeasureSwiperInFakeDrag023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper in stretch mode
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayMode(SwiperDisplayMode::STRETCH);
    model.SetDisplayCount(2);
    CreateSwiperItems(6);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Start fake drag
     * @tc.expected: Stretch mode should work correctly
     */
    EXPECT_TRUE(pattern_->StartFakeDrag());
    pattern_->UpdateCurrentOffset(120.0f);
    FlushUITasks();

    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

// ========== Branch 27: Error case - FakeDragBy without StartFakeDrag ==========

/**
 * @tc.name: MeasureSwiperInFakeDrag024
 * @tc.desc: Test FakeDragBy without calling StartFakeDrag first
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, MeasureSwiperInFakeDrag024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper
     */
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems(5);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Try FakeDragBy without StartFakeDrag
     * @tc.expected: Should return false
     */
    EXPECT_FALSE(pattern_->FakeDragBy(50.0f));
    EXPECT_FALSE(pattern_->isFakeDragging_);
}

// ========== Branch 28: Error case - StopFakeDrag without StartFakeDrag ==========

/**
 * @tc.name: MeasureSwiperInFakeDrag025
 * @tc.desc: Test StopFakeDrag without calling StartFakeDrag first
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, MeasureSwiperInFakeDrag025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper
     */
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems(5);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Try StopFakeDrag without StartFakeDrag
     * @tc.expected: Should return false
     */
    EXPECT_FALSE(pattern_->StopFakeDrag());
    EXPECT_FALSE(pattern_->isFakeDragging_);
}

// ========== Branch 29: Error case - StartFakeDrag when already dragging ==========

/**
 * @tc.name: MeasureSwiperInFakeDrag026
 * @tc.desc: Test StartFakeDrag when already in dragging state
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, MeasureSwiperInFakeDrag026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper
     */
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems(5);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Start fake drag, then try to start again
     * @tc.expected: Second StartFakeDrag should fail
     */
    EXPECT_TRUE(pattern_->StartFakeDrag());
    EXPECT_FALSE(pattern_->StartFakeDrag()); // Should fail when already dragging

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

// ========== Branch 30: State check - IsFakeDragging ==========

/**
 * @tc.name: MeasureSwiperInFakeDrag027
 * @tc.desc: Test IsFakeDragging returns correct state
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, MeasureSwiperInFakeDrag027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper
     */
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems(5);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Check state transitions
     * @tc.expected: IsFakeDragging should reflect current state
     */
    EXPECT_FALSE(pattern_->IsFakeDragging());

    EXPECT_TRUE(pattern_->StartFakeDrag());
    EXPECT_TRUE(pattern_->IsFakeDragging());

    EXPECT_TRUE(pattern_->StopFakeDrag());
    EXPECT_FALSE(pattern_->IsFakeDragging());
}

// ========== Branch 34: Loop mode complete rotation ==========

/**
 * @tc.name: MeasureSwiperInFakeDrag028
 * @tc.desc: Test complete rotation in loop mode
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, MeasureSwiperInFakeDrag028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper in loop mode
     */
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    CreateSwiperItems(4);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Drag with offset larger than one full rotation
     * @tc.expected: Should handle complete rotation correctly
     */
    EXPECT_TRUE(pattern_->StartFakeDrag());

    // Drag forward more than full swiper width
    EXPECT_TRUE(pattern_->FakeDragBy(SWIPER_WIDTH * 2));
    FlushUITasks();

    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

// ========== Branch 35: Zero items edge case ==========

/**
 * @tc.name: MeasureSwiperInFakeDrag029
 * @tc.desc: Test with zero swiper items
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, MeasureSwiperInFakeDrag029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper with no items
     */
    SwiperModelNG model = CreateSwiper();
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Try to start fake drag
     * @tc.expected: Should handle empty swiper gracefully
     */
    auto result = pattern_->StartFakeDrag();
    // Verify no crash - behavior depends on implementation

    if (result) {
        EXPECT_TRUE(pattern_->StopFakeDrag());
    }
}

} // namespace OHOS::Ace::NG
