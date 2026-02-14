/**
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"
#include "swiper_test_ng.h"

namespace OHOS::Ace::NG {

// ============================================================
// Part 1: FakeDrag API Interface Tests (FakeDrag001-026)
// ============================================================

// ========== StartFakeDrag Tests ==========

/**
 * @tc.name: FakeDrag001
 * @tc.desc: Test StartFakeDrag when isDragging or isFakeDragging is true
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems(5);
    CreateSwiperDone();

    pattern_->isDragging_ = true;
    EXPECT_FALSE(pattern_->StartFakeDrag());

    pattern_->isDragging_ = false;
    pattern_->isFakeDragging_ = true;
    EXPECT_FALSE(pattern_->StartFakeDrag());
}

/**
 * @tc.name: FakeDrag002
 * @tc.desc: Test StartFakeDrag when both flags are false
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems(5);
    CreateSwiperDone();

    EXPECT_TRUE(pattern_->StartFakeDrag());
    EXPECT_TRUE(pattern_->isFakeDragging_);
    EXPECT_TRUE(pattern_->StopFakeDrag());
}

// ========== FakeDragBy Tests ==========

/**
 * @tc.name: FakeDrag003
 * @tc.desc: Test FakeDragBy when not fake dragging
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag003, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems(5);
    CreateSwiperDone();

    EXPECT_FALSE(pattern_->FakeDragBy(100.0f));
}

/**
 * @tc.name: FakeDrag004
 * @tc.desc: Test FakeDragBy with empty itemPosition
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag004, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperDone();

    EXPECT_TRUE(pattern_->StartFakeDrag());
    EXPECT_FALSE(pattern_->FakeDragBy(100.0f));
    EXPECT_TRUE(pattern_->StopFakeDrag());
}

/**
 * @tc.name: FakeDrag005
 * @tc.desc: Test FakeDragBy with near-zero offset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag005, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems(5);
    CreateSwiperDone();
    EXPECT_TRUE(pattern_->StartFakeDrag());

    EXPECT_FALSE(pattern_->FakeDragBy(0.0f));
    EXPECT_TRUE(pattern_->StopFakeDrag());
}

/**
 * @tc.name: FakeDrag006
 * @tc.desc: Test FakeDragBy with lastDragByOffset_ set
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag006, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    CreateSwiperItems(5);
    CreateSwiperDone();
    EXPECT_TRUE(pattern_->StartFakeDrag());

    EXPECT_TRUE(pattern_->FakeDragBy(50.0f));
    // Note: Check immediately after FakeDragBy, before FlushUITasks resets lastDragByOffset_
    EXPECT_TRUE(pattern_->lastDragByOffset_.has_value());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

/**
 * @tc.name: FakeDrag007
 * @tc.desc: Test FakeDragBy with positive offset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag007, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    CreateSwiperItems(5);
    CreateSwiperDone();

    EXPECT_TRUE(pattern_->StartFakeDrag());
    EXPECT_TRUE(pattern_->FakeDragBy(100.0f));
    FlushUITasks();
    EXPECT_TRUE(pattern_->StopFakeDrag());
}

/**
 * @tc.name: FakeDrag008
 * @tc.desc: Test FakeDragBy with negative offset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag008, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    CreateSwiperItems(5);
    CreateSwiperDone();

    EXPECT_TRUE(pattern_->StartFakeDrag());
    EXPECT_TRUE(pattern_->FakeDragBy(-100.0f));
    FlushUITasks();
    EXPECT_TRUE(pattern_->StopFakeDrag());
}

/**
 * @tc.name: FakeDrag009
 * @tc.desc: Test FakeDragBy when FakeDragCheckAtStart returns false
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag009, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    CreateSwiperItems(5);
    CreateSwiperDone();

    EXPECT_TRUE(pattern_->StartFakeDrag());
    (void)pattern_->FakeDragBy(-1000.0f);
    EXPECT_TRUE(pattern_->StopFakeDrag());
}

/**
 * @tc.name: FakeDrag010
 * @tc.desc: Test FakeDragBy when boundary check succeeds
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag010, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    CreateSwiperItems(5);
    CreateSwiperDone();

    EXPECT_TRUE(pattern_->StartFakeDrag());
    EXPECT_TRUE(pattern_->FakeDragBy(50.0f));
    FlushUITasks();
    EXPECT_TRUE(pattern_->StopFakeDrag());
}

// ========== StopFakeDrag Tests ==========

/**
 * @tc.name: FakeDrag011
 * @tc.desc: Test StopFakeDrag when not fake dragging
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag011, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems(5);
    CreateSwiperDone();

    EXPECT_FALSE(pattern_->StopFakeDrag());
}

/**
 * @tc.name: FakeDrag012
 * @tc.desc: Test StopFakeDrag success
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag012, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    CreateSwiperItems(5);
    CreateSwiperDone();

    EXPECT_TRUE(pattern_->StartFakeDrag());
    EXPECT_TRUE(pattern_->FakeDragBy(50.0f));
    FlushUITasks();

    EXPECT_TRUE(pattern_->StopFakeDrag());
    EXPECT_FALSE(pattern_->isFakeDragging_);
}

/**
 * @tc.name: FakeDrag013
 * @tc.desc: Test StopFakeDrag with VERTICAL direction
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag013, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    model.SetLoop(true);
    CreateSwiperItems(5);
    CreateSwiperDone();

    EXPECT_TRUE(pattern_->StartFakeDrag());
    EXPECT_TRUE(pattern_->FakeDragBy(50.0f));
    FlushUITasks();

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

/**
 * @tc.name: FakeDrag014
 * @tc.desc: Test StopFakeDrag with HORIZONTAL direction
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag014, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    CreateSwiperItems(5);
    CreateSwiperDone();

    EXPECT_TRUE(pattern_->StartFakeDrag());
    EXPECT_TRUE(pattern_->FakeDragBy(50.0f));
    FlushUITasks();

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

// ========== FakeDragCheckAtStart Tests ==========

/**
 * @tc.name: FakeDrag015
 * @tc.desc: Test FakeDragCheckAtStart with hasCachedCapture_
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag015, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems(5);
    CreateSwiperDone();

    pattern_->hasCachedCapture_ = true;
    pattern_->contentMainSize_ = 500.0f;
    float offset = 600.0f;
    EXPECT_TRUE(pattern_->FakeDragCheckAtStart(offset));
    EXPECT_FLOAT_EQ(offset, fmod(600.0f, 500.0f));
}

/**
 * @tc.name: FakeDrag016
 * @tc.desc: Test FakeDragCheckAtStart in loop mode
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag016, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    CreateSwiperItems(5);
    CreateSwiperDone();

    float offset = 100.0f;
    EXPECT_TRUE(pattern_->FakeDragCheckAtStart(offset));
}

/**
 * @tc.name: FakeDrag017
 * @tc.desc: Test FakeDragCheckAtStart at boundary with ignoreBlankOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag017, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetIndex(0);
    CreateSwiperItems(5);
    CreateSwiperDone();

    pattern_->ignoreBlankOffset_ = 50.0f;
    float offset = 100.0f;
    EXPECT_TRUE(pattern_->FakeDragCheckAtStart(offset));
}

/**
 * @tc.name: FakeDrag019
 * @tc.desc: Test FakeDragCheckAtStart success path
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag019, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetIndex(0);
    CreateSwiperItems(5);
    CreateSwiperDone();

    float offset = 10.0f;
    EXPECT_TRUE(pattern_->FakeDragCheckAtStart(offset));
}

// ========== FakeDragCheckAtEnd Tests ==========

/**
 * @tc.name: FakeDrag020
 * @tc.desc: Test FakeDragCheckAtEnd with hasCachedCapture_
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag020, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems(5);
    CreateSwiperDone();

    pattern_->hasCachedCapture_ = true;
    pattern_->contentMainSize_ = 500.0f;
    float offset = -600.0f;
    EXPECT_TRUE(pattern_->FakeDragCheckAtEnd(offset));
    EXPECT_FLOAT_EQ(offset, fmod(-600.0f, -500.0f));
}

/**
 * @tc.name: FakeDrag021
 * @tc.desc: Test FakeDragCheckAtEnd in loop mode
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag021, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    CreateSwiperItems(5);
    CreateSwiperDone();

    float offset = -100.0f;
    EXPECT_TRUE(pattern_->FakeDragCheckAtEnd(offset));
}

/**
 * @tc.name: FakeDrag022
 * @tc.desc: Test FakeDragCheckAtEnd at boundary with ignoreBlankOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag022, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetIndex(4);
    CreateSwiperItems(5);
    CreateSwiperDone();

    pattern_->ignoreBlankOffset_ = 50.0f;
    float offset = -100.0f;
    EXPECT_TRUE(pattern_->FakeDragCheckAtEnd(offset));
}

/**
 * @tc.name: FakeDrag024
 * @tc.desc: Test FakeDragCheckAtEnd success path
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag024, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetIndex(4);
    CreateSwiperItems(5);
    CreateSwiperDone();

    float offset = -10.0f;
    EXPECT_TRUE(pattern_->FakeDragCheckAtEnd(offset));
}

// ========== Integration Tests ==========

/**
 * @tc.name: FakeDrag025
 * @tc.desc: Test complete fake drag flow
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag025, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    CreateSwiperItems(5);
    CreateSwiperDone();

    EXPECT_TRUE(pattern_->StartFakeDrag());
    EXPECT_TRUE(pattern_->FakeDragBy(100.0f));
    FlushUITasks();
    EXPECT_TRUE(pattern_->FakeDragBy(-50.0f));
    FlushUITasks();
    EXPECT_TRUE(pattern_->StopFakeDrag());
}

/**
 * @tc.name: FakeDrag026
 * @tc.desc: Test IsFakeDragging state
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag026, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems(5);
    CreateSwiperDone();

    EXPECT_FALSE(pattern_->IsFakeDragging());

    EXPECT_TRUE(pattern_->StartFakeDrag());
    EXPECT_TRUE(pattern_->IsFakeDragging());

    EXPECT_TRUE(pattern_->StopFakeDrag());
    EXPECT_FALSE(pattern_->isFakeDragging_);
}

// ============================================================
// Part 2: FakeDrag Layout Algorithm Tests (FakeDrag027-055)
// ============================================================

/**
 * @tc.name: FakeDrag027
 * @tc.desc: Test MeasureSwiperInFakeDrag with positive offset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag027, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    CreateSwiperItems(5);
    CreateSwiperDone();

    EXPECT_TRUE(pattern_->StartFakeDrag());
    EXPECT_TRUE(pattern_->isFakeDragging_);

    pattern_->UpdateCurrentOffset(100.0f);
    FlushUITasks();

    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

/**
 * @tc.name: FakeDrag028
 * @tc.desc: Test MeasureSwiperInFakeDrag with negative offset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag028, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    CreateSwiperItems(5);
    CreateSwiperDone();

    EXPECT_TRUE(pattern_->StartFakeDrag());
    EXPECT_TRUE(pattern_->isFakeDragging_);

    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();

    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

/**
 * @tc.name: FakeDrag029
 * @tc.desc: Test MeasureSwiperInFakeDrag with zero offset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag029, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems(5);
    CreateSwiperDone();

    EXPECT_TRUE(pattern_->StartFakeDrag());
    EXPECT_TRUE(pattern_->isFakeDragging_);

    pattern_->UpdateCurrentOffset(0.0f);
    FlushUITasks();

    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

/**
 * @tc.name: FakeDrag030
 * @tc.desc: Test with prevMargin set
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag030, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetPreviousMargin(Dimension(20.0_vp), false);
    CreateSwiperItems(5);
    CreateSwiperDone();

    EXPECT_TRUE(pattern_->StartFakeDrag());
    pattern_->UpdateCurrentOffset(50.0f);
    FlushUITasks();

    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

/**
 * @tc.name: FakeDrag031
 * @tc.desc: Test without prevMargin
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag031, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems(5);
    CreateSwiperDone();

    EXPECT_TRUE(pattern_->StartFakeDrag());
    pattern_->UpdateCurrentOffset(50.0f);
    FlushUITasks();

    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

/**
 * @tc.name: FakeDrag032
 * @tc.desc: Test with nextMargin set
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag032, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetNextMargin(Dimension(30.0_vp), false);
    CreateSwiperItems(5);
    CreateSwiperDone();

    EXPECT_TRUE(pattern_->StartFakeDrag());
    pattern_->UpdateCurrentOffset(-50.0f);
    FlushUITasks();

    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

/**
 * @tc.name: FakeDrag033
 * @tc.desc: Test without nextMargin
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag033, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems(5);
    CreateSwiperDone();

    EXPECT_TRUE(pattern_->StartFakeDrag());
    pattern_->UpdateCurrentOffset(-50.0f);
    FlushUITasks();

    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

/**
 * @tc.name: FakeDrag034
 * @tc.desc: Test non-loop mode with forward boundary
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag034, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    CreateSwiperItems(5);
    CreateSwiperDone();

    pattern_->currentIndex_ = 4;
    FlushUITasks();

    EXPECT_TRUE(pattern_->StartFakeDrag());
    pattern_->UpdateCurrentOffset(200.0f);
    FlushUITasks();

    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

/**
 * @tc.name: FakeDrag035
 * @tc.desc: Test non-loop mode with backward boundary
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag035, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    CreateSwiperItems(5);
    CreateSwiperDone();

    pattern_->currentIndex_ = 0;
    FlushUITasks();

    EXPECT_TRUE(pattern_->StartFakeDrag());
    pattern_->UpdateCurrentOffset(-200.0f);
    FlushUITasks();

    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

/**
 * @tc.name: FakeDrag036
 * @tc.desc: Test prevention of circular layout in loop mode
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag036, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    CreateSwiperItems(3);
    CreateSwiperDone();

    EXPECT_TRUE(pattern_->StartFakeDrag());
    pattern_->UpdateCurrentOffset(500.0f);
    FlushUITasks();

    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

/**
 * @tc.name: FakeDrag037
 * @tc.desc: Test swipeByGroup mode with forward drag
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag037, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(2);
    model.SetSwipeByGroup(true);
    CreateSwiperItems(8);
    CreateSwiperDone();

    EXPECT_TRUE(pattern_->StartFakeDrag());
    pattern_->UpdateCurrentOffset(150.0f);
    FlushUITasks();

    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

/**
 * @tc.name: FakeDrag038
 * @tc.desc: Test swipeByGroup mode with backward drag
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag038, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(2);
    model.SetSwipeByGroup(true);
    CreateSwiperItems(8);
    CreateSwiperDone();

    EXPECT_TRUE(pattern_->StartFakeDrag());
    pattern_->UpdateCurrentOffset(-150.0f);
    FlushUITasks();

    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

/**
 * @tc.name: FakeDrag039
 * @tc.desc: Test reaching last item in loop mode
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag039, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    CreateSwiperItems(5);
    CreateSwiperDone();

    EXPECT_TRUE(pattern_->StartFakeDrag());
    pattern_->UpdateCurrentOffset(400.0f);
    FlushUITasks();

    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

/**
 * @tc.name: FakeDrag040
 * @tc.desc: Test reaching first item in loop mode
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag040, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    CreateSwiperItems(5);
    CreateSwiperDone();

    EXPECT_TRUE(pattern_->StartFakeDrag());
    pattern_->UpdateCurrentOffset(-400.0f);
    FlushUITasks();

    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

/**
 * @tc.name: FakeDrag041
 * @tc.desc: Test removing items before startEdgePos
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag041, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems(10);
    CreateSwiperDone();

    EXPECT_TRUE(pattern_->StartFakeDrag());
    pattern_->UpdateCurrentOffset(400.0f);
    FlushUITasks();

    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

/**
 * @tc.name: FakeDrag042
 * @tc.desc: Test removing items after endEdgePos
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag042, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems(10);
    CreateSwiperDone();

    EXPECT_TRUE(pattern_->StartFakeDrag());
    pattern_->UpdateCurrentOffset(-400.0f);
    FlushUITasks();

    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

/**
 * @tc.name: FakeDrag043
 * @tc.desc: Test with nextMarginIgnoreBlank enabled
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag043, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetNextMargin(Dimension(30.0_vp), true);
    CreateSwiperItems(5);
    CreateSwiperDone();

    pattern_->currentIndex_ = 4;
    FlushUITasks();

    EXPECT_TRUE(pattern_->StartFakeDrag());
    pattern_->UpdateCurrentOffset(100.0f);
    FlushUITasks();

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

/**
 * @tc.name: FakeDrag044
 * @tc.desc: Test with prevMarginIgnoreBlank enabled
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag044, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetPreviousMargin(Dimension(20.0_vp), true);
    CreateSwiperItems(5);
    CreateSwiperDone();

    pattern_->currentIndex_ = 0;
    FlushUITasks();

    EXPECT_TRUE(pattern_->StartFakeDrag());
    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

/**
 * @tc.name: FakeDrag045
 * @tc.desc: Test with itemSpace set
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag045, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetItemSpace(15.0_vp);
    CreateSwiperItems(5);
    CreateSwiperDone();

    EXPECT_TRUE(pattern_->StartFakeDrag());
    pattern_->UpdateCurrentOffset(100.0f);
    FlushUITasks();

    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

/**
 * @tc.name: FakeDrag046
 * @tc.desc: Test with ignoreBlankOffset set via prevMarginIgnoreBlank
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag046, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetPreviousMargin(Dimension(20.0_vp), true);
    CreateSwiperItems(5);
    CreateSwiperDone();

    pattern_->currentIndex_ = 0;
    FlushUITasks();

    EXPECT_TRUE(pattern_->StartFakeDrag());
    pattern_->UpdateCurrentOffset(-50.0f);
    FlushUITasks();

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

/**
 * @tc.name: FakeDrag047
 * @tc.desc: Test multiple FakeDragBy calls
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag047, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems(5);
    CreateSwiperDone();

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

/**
 * @tc.name: FakeDrag048
 * @tc.desc: Test fake drag in vertical direction
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag048, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems(5);
    CreateSwiperDone();

    EXPECT_EQ(layoutProperty_->GetDirection().value(), Axis::VERTICAL);

    EXPECT_TRUE(pattern_->StartFakeDrag());
    pattern_->UpdateCurrentOffset(100.0f);
    FlushUITasks();

    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

/**
 * @tc.name: FakeDrag049
 * @tc.desc: Test fake drag in stretch mode
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag049, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayMode(SwiperDisplayMode::STRETCH);
    model.SetDisplayCount(2);
    CreateSwiperItems(6);
    CreateSwiperDone();

    EXPECT_TRUE(pattern_->StartFakeDrag());
    pattern_->UpdateCurrentOffset(120.0f);
    FlushUITasks();

    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

/**
 * @tc.name: FakeDrag050
 * @tc.desc: Test FakeDragBy without calling StartFakeDrag first
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag050, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems(5);
    CreateSwiperDone();

    EXPECT_FALSE(pattern_->FakeDragBy(50.0f));
    EXPECT_FALSE(pattern_->isFakeDragging_);
}

/**
 * @tc.name: FakeDrag051
 * @tc.desc: Test StopFakeDrag without calling StartFakeDrag first
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag051, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems(5);
    CreateSwiperDone();

    EXPECT_FALSE(pattern_->StopFakeDrag());
    EXPECT_FALSE(pattern_->isFakeDragging_);
}

/**
 * @tc.name: FakeDrag052
 * @tc.desc: Test StartFakeDrag when already in dragging state
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag052, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems(5);
    CreateSwiperDone();

    EXPECT_TRUE(pattern_->StartFakeDrag());
    EXPECT_FALSE(pattern_->StartFakeDrag());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

/**
 * @tc.name: FakeDrag053
 * @tc.desc: Test complete rotation in loop mode
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag053, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    CreateSwiperItems(4);
    CreateSwiperDone();

    EXPECT_TRUE(pattern_->StartFakeDrag());

    EXPECT_TRUE(pattern_->FakeDragBy(SWIPER_WIDTH * 2));
    FlushUITasks();

    EXPECT_FALSE(pattern_->itemPosition_.empty());

    EXPECT_TRUE(pattern_->StopFakeDrag());
}

/**
 * @tc.name: FakeDrag054
 * @tc.desc: Test with zero swiper items
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FakeDrag054, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperDone();

    auto result = pattern_->StartFakeDrag();

    if (result) {
        EXPECT_TRUE(pattern_->StopFakeDrag());
    }
}

} // namespace OHOS::Ace::NG
