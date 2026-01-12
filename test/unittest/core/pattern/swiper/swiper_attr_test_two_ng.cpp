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
#include "test/mock/core/pattern/mock_nestable_scroll_container.h"

#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_paint_method.h"
#include "core/components_ng/pattern/swiper/swiper_change_event.h"
namespace OHOS::Ace::NG {
class SwiperAttrTestTwoNg : public SwiperTestNg {};

/**
 * @tc.name: OnScrollDragEndRecursive001
 * @tc.desc: Test OnScrollDragEndRecursive method about NestableScrollContainer
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestTwoNg, OnScrollDragEndRecursive001, TestSize.Level1)
{
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_FIRST,
        .backward = NestedScrollMode::SELF_ONLY,
    };
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetNestedScroll(nestedOpt);
    CreateSwiperItems();
    CreateSwiperDone();
    auto mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*mockScroll, OnScrollDragEndRecursive()).Times(1);
    ASSERT_EQ(mockScroll->parent_.Upgrade(), nullptr);
    /**
     * @tc.steps: step1. call OnScrollDragEndRecursive in parent and nestedScroll_.NeedParent() combined condition
     */
    pattern_->parent_ = mockScroll;
    ASSERT_NE(pattern_->parent_.Upgrade(), nullptr);
    EXPECT_TRUE(pattern_->nestedScroll_.NeedParent());
    pattern_->OnScrollDragEndRecursive();

    nestedOpt = {
        .forward = NestedScrollMode::SELF_ONLY,
        .backward = NestedScrollMode::SELF_ONLY,
    };
    pattern_->nestedScroll_ = nestedOpt;
    ASSERT_NE(pattern_->parent_.Upgrade(), nullptr);
    EXPECT_FALSE(pattern_->nestedScroll_.NeedParent());
    pattern_->OnScrollDragEndRecursive();

    nestedOpt = {
        .forward = NestedScrollMode::SELF_FIRST,
        .backward = NestedScrollMode::SELF_ONLY,
    };
    pattern_->nestedScroll_ = nestedOpt;
    pattern_->parent_ = nullptr;
    EXPECT_TRUE(pattern_->nestedScroll_.NeedParent());
    pattern_->OnScrollDragEndRecursive();

    nestedOpt = {
        .forward = NestedScrollMode::SELF_ONLY,
        .backward = NestedScrollMode::SELF_ONLY,
    };
    pattern_->nestedScroll_ = nestedOpt;
    EXPECT_FALSE(pattern_->nestedScroll_.NeedParent());
    pattern_->OnScrollDragEndRecursive();
}

/**
 * @tc.name: LoopChange001
 * @tc.desc: Test loop change with prevMargin
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestTwoNg, LoopChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. loop is false
     * @tc.expected: The first node in the display area is 0
     */
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetPreviousMargin(Dimension(PRE_MARGIN), false);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->itemPosition_.find(-1), pattern_->itemPosition_.end());

    /**
     * @tc.steps: step2. loop changes to true
     * @tc.expected: The first node in the display area is -1
     */
    layoutProperty_->UpdateLoop(true);
    pattern_->OnModifyDone();
    FlushUITasks();
    EXPECT_NE(pattern_->itemPosition_.find(-1), pattern_->itemPosition_.end());
}

/**
 * @tc.name: PageFlipModeTest001
 * @tc.desc: PageFlipMode property test
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestTwoNg, PageFlipModeTest001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    // default mode is PageFlipMode::CONTINUOUS(0)
    EXPECT_EQ(pattern_->GetPageFlipMode(), 0);
    // mode is PageFlipMode::SINGLE(0)
    model.SetPageFlipMode(AceType::RawPtr(frameNode_), 1);
    EXPECT_EQ(pattern_->GetPageFlipMode(), 1);
    // exceeding the enum range will reset to default
    model.SetPageFlipMode(AceType::RawPtr(frameNode_), -1);
    EXPECT_EQ(pattern_->GetPageFlipMode(), 0);
    // exceeding the enum range will reset to default
    model.SetPageFlipMode(AceType::RawPtr(frameNode_), 100);
    EXPECT_EQ(pattern_->GetPageFlipMode(), 0);
}

/**
 * @tc.name: ShowCachedItems013
 * @tc.desc: Test show cached items on RTL, loop = true, displayCount = 3
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestTwoNg, ShowCachedItems013, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    model.SetCachedIsShown(true);
    model.SetDisplayCount(3);
    model.SetCachedCount(1);
    model.SetIndex(3);
    CreateSwiperItems(10);
    CreateSwiperDone();

    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    FlushUITasks();

    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, 480.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 320.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 160.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -160.0f);

    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 6);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, 540.0f);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, 380.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 220.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 60.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -100.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -260.0f);

    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 6);
    EXPECT_EQ(pattern_->itemPosition_[8].startPos, 600.0f);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, 440.0f);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, 280.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 120.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, -40.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -200.0f);

    pattern_->ChangeIndex(7, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[10].startPos, 480.0f);
    EXPECT_EQ(pattern_->itemPosition_[9].startPos, 320.0f);
    EXPECT_EQ(pattern_->itemPosition_[8].startPos, 160.0f);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, -160.0f);
}

/**
 * @tc.name: ShowCachedItems014
 * @tc.desc: Test show cached items on RTL, loop = true, cachedCount = 2, set nextMargin and prevMargin
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestTwoNg, ShowCachedItems014, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    model.SetCachedIsShown(true);
    model.SetDisplayCount(1);
    model.SetCachedCount(2);
    model.SetIndex(4);
    model.SetNextMargin(Dimension(10, DimensionUnit::PX), false);
    model.SetPreviousMargin(Dimension(10, DimensionUnit::PX), false);
    model.SetItemSpace(Dimension(10, DimensionUnit::PX));
    CreateSwiperItems(10);
    CreateSwiperDone();

    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    FlushUITasks();

    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 7);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, 1350.0f);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, 900.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 450.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].endPos, 890.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].endPos, 440.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -450.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -900.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -1350.0f);

    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 6);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, 1250.0f);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, 800.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 350.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, -100.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -550.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -1000.0f);

    pattern_->ChangeIndex(5, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 7);
    EXPECT_EQ(pattern_->itemPosition_[8].startPos, 1350.0f);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, 900.0f);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, 450.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, -450.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -900.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -1350.0f);

    pattern_->ChangeIndex(9, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 7);
    EXPECT_EQ(pattern_->itemPosition_[12].startPos, 1350.0f);
    EXPECT_EQ(pattern_->itemPosition_[11].startPos, 900.0f);
    EXPECT_EQ(pattern_->itemPosition_[10].startPos, 450.0f);
    EXPECT_EQ(pattern_->itemPosition_[9].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[8].startPos, -450.0f);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, -900.0f);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, -1350.0f);
}

/**
 * @tc.name: ShowCachedItems015
 * @tc.desc: Test show cached items on vertical = true, loop = true, cachedCount = 1
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestTwoNg, ShowCachedItems015, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    model.SetDirection(Axis::VERTICAL);
    model.SetCachedIsShown(true);
    model.SetDisplayCount(1);
    model.SetCachedCount(1);
    model.SetIndex(0);
    CreateSwiperItems(5);
    CreateSwiperDone();
    FlushUITasks();

    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 3);
    EXPECT_EQ(pattern_->itemPosition_[-1].startPos, -800.0f);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 800.0f);

    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 4);
    EXPECT_EQ(pattern_->itemPosition_[-1].startPos, -900.0f);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -100.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 700.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 1500.0f);

    pattern_->ChangeIndex(1, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 3);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -800.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 800.0f);

    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 4);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -900.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -100.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 700.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 1500.0f);

    pattern_->ChangeIndex(4, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 3);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -800.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 800.0f);
}

/**
 * @tc.name: ShowCachedItems016
 * @tc.desc: Test show cached items on vertical = true, loop = true, cachedCount = 2, set nextMargin and prevMargin
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestTwoNg, ShowCachedItems016, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    model.SetDirection(Axis::VERTICAL);
    model.SetCachedIsShown(true);
    model.SetDisplayCount(1);
    model.SetCachedCount(2);
    model.SetIndex(1);
    model.SetNextMargin(Dimension(10, DimensionUnit::PX), false);
    model.SetPreviousMargin(Dimension(10, DimensionUnit::PX), false);
    model.SetItemSpace(Dimension(10, DimensionUnit::PX));
    CreateSwiperItems(5);
    CreateSwiperDone();
    FlushUITasks();

    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[-1].startPos, -1540.0f);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -770.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 770.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 1540.0f);

    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -870.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -100.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 670.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 1440.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 2210.0f);

    pattern_->ChangeIndex(2, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -1540.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -770.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 770.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 1540.0f);

    pattern_->ChangeIndex(4, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -1540.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -770.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 770.0f);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, 1540.0f);
}

/**
 * @tc.name: ShowCachedItems017
 * @tc.desc: Test show cached items on vertical = true, cachedCount = 2, displayCount = 2, set nextMargin and prevMargin
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestTwoNg, ShowCachedItems017, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    model.SetDirection(Axis::VERTICAL);
    model.SetCachedIsShown(true);
    model.SetDisplayCount(2);
    model.SetCachedCount(2);
    model.SetIndex(4);
    model.SetNextMargin(Dimension(10, DimensionUnit::PX), false);
    model.SetPreviousMargin(Dimension(10, DimensionUnit::PX), false);
    model.SetItemSpace(Dimension(10, DimensionUnit::PX));
    CreateSwiperItems(10);
    CreateSwiperDone();
    FlushUITasks();

    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 8);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -1155.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -770.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -385.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 385.0f);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, 770.0f);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, 1155.0f);
    EXPECT_EQ(pattern_->itemPosition_[8].startPos, 1540.0f);

    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 7);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -870.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -485.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, -100.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 285.0f);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, 670.0f);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, 1055.0f);
    EXPECT_EQ(pattern_->itemPosition_[8].startPos, 1440.0f);

    pattern_->ChangeIndex(5, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 8);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -1155.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -770.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, -385.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, 385.0f);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, 770.0f);
    EXPECT_EQ(pattern_->itemPosition_[8].startPos, 1155.0f);
    EXPECT_EQ(pattern_->itemPosition_[9].startPos, 1540.0f);

    pattern_->ChangeIndex(9, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 8);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, -1155.0f);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, -770.0f);
    EXPECT_EQ(pattern_->itemPosition_[8].startPos, -385.0f);
    EXPECT_EQ(pattern_->itemPosition_[9].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[10].startPos, 385.0f);
    EXPECT_EQ(pattern_->itemPosition_[11].startPos, 770.0f);
    EXPECT_EQ(pattern_->itemPosition_[12].startPos, 1155.0f);
    EXPECT_EQ(pattern_->itemPosition_[13].startPos, 1540.0f);
}

/**
 * @tc.name: ShowCachedItems018
 * @tc.desc: Test show cached items on swipe by group, loop = true, displayCount = 3
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestTwoNg, ShowCachedItems018, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    model.SetSwipeByGroup(true);
    model.SetCachedIsShown(true);
    model.SetDisplayCount(3);
    model.SetCachedCount(1);
    model.SetIndex(0);
    CreateSwiperItems(10);
    CreateSwiperDone();
    FlushUITasks();

    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 9);
    EXPECT_EQ(pattern_->itemPosition_[-3].startPos, -480.0f);
    EXPECT_EQ(pattern_->itemPosition_[-2].startPos, -320.0f);
    EXPECT_EQ(pattern_->itemPosition_[-1].startPos, -160.0f);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 160.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 320.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 480.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 640.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 800.0f);

    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 12);
    EXPECT_EQ(pattern_->itemPosition_[-3].startPos, -580.0f);
    EXPECT_EQ(pattern_->itemPosition_[-2].startPos, -420.0f);
    EXPECT_EQ(pattern_->itemPosition_[-1].startPos, -260.0f);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -100.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 60.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 220.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 380.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 540.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 700.0f);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, 860.0f);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, 1020.0f);
    EXPECT_EQ(pattern_->itemPosition_[8].startPos, 1180.0f);

    pattern_->ChangeIndex(3, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 9);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -480.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -320.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -160.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 160.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 320.0f);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, 480.0f);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, 640.0f);
    EXPECT_EQ(pattern_->itemPosition_[8].startPos, 800.0f);

    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 12);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -580.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -420.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -260.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -100.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 60.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 220.0f);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, 380.0f);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, 540.0f);
    EXPECT_EQ(pattern_->itemPosition_[8].startPos, 700.0f);
    EXPECT_EQ(pattern_->itemPosition_[9].startPos, 860.0f);
    EXPECT_EQ(pattern_->itemPosition_[10].startPos, 1020.0f);
    EXPECT_EQ(pattern_->itemPosition_[11].startPos, 1180.0f);

    pattern_->ChangeIndex(9, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 9);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, -480.0f);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, -320.0f);
    EXPECT_EQ(pattern_->itemPosition_[8].startPos, -160.0f);
    EXPECT_EQ(pattern_->itemPosition_[9].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[10].startPos, 160.0f);
    EXPECT_EQ(pattern_->itemPosition_[11].startPos, 320.0f);
    EXPECT_EQ(pattern_->itemPosition_[12].startPos, 480.0f);
    EXPECT_EQ(pattern_->itemPosition_[13].startPos, 640.0f);
    EXPECT_EQ(pattern_->itemPosition_[14].startPos, 800.0f);
}

/**
 * @tc.name: ShowCachedItems020
 * @tc.desc: Test show cached items on nextMargin ignore blank
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestTwoNg, ShowCachedItems020, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetCachedIsShown(true);
    model.SetDisplayCount(1);
    model.SetCachedCount(1);
    model.SetIndex(0);
    model.SetNextMargin(Dimension(10, DimensionUnit::PX), true);
    CreateSwiperItems(5);
    CreateSwiperDone();
    FlushUITasks();

    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 3);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 470.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 940.0f);

    pattern_->ChangeIndex(2, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 4);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -470.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 470.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 940.0f);

    pattern_->UpdateCurrentOffset(5.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -935.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -465.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 5.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 475.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 945.0f);

    pattern_->ChangeIndex(4, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 3);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -940.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -470.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 0.0f);
}

/**
 * @tc.name: ShowCachedItems021
 * @tc.desc: Test show cached items on prevMargin ignore blank
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestTwoNg, ShowCachedItems021, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetCachedIsShown(true);
    model.SetDisplayCount(1);
    model.SetCachedCount(1);
    model.SetIndex(4);
    model.SetPreviousMargin(Dimension(10, DimensionUnit::PX), true);
    CreateSwiperItems(5);
    CreateSwiperDone();
    FlushUITasks();

    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 3);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -940.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -470.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 0.0f);

    pattern_->ChangeIndex(2, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 4);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -940.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -470.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 470.0f);

    pattern_->UpdateCurrentOffset(-5.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -945.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -475.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -5.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 465.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 935.0f);

    pattern_->ChangeIndex(0, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 3);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 470.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 940.0f);
}

/**
 * @tc.name: ShowCachedItems022
 * @tc.desc: Test show cached items on prevMargin and nextMargin ignore blank
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestTwoNg, ShowCachedItems022, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetCachedIsShown(true);
    model.SetDisplayCount(1);
    model.SetCachedCount(1);
    model.SetIndex(2);
    model.SetPreviousMargin(Dimension(10, DimensionUnit::PX), true);
    model.SetNextMargin(Dimension(10, DimensionUnit::PX), true);
    CreateSwiperItems(5);
    CreateSwiperDone();
    FlushUITasks();

    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -920.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -460.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 460.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 920.0f);

    pattern_->ChangeIndex(0, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 3);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 460.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 920.0f);

    pattern_->ChangeIndex(4, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 3);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -920.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -460.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 0.0f);
}

/**
 * @tc.name: ShowCachedItems023
 * @tc.desc: Test show cached items on prevMargin and nextMargin ignore blank
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestTwoNg, ShowCachedItems023, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetCachedIsShown(true);
    model.SetDisplayCount(1);
    model.SetCachedCount(3);
    model.SetIndex(2);
    model.SetPreviousMargin(Dimension(10, DimensionUnit::PX), true);
    model.SetNextMargin(Dimension(10, DimensionUnit::PX), true);
    CreateSwiperItems(5);
    CreateSwiperDone();
    FlushUITasks();

    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -920.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -460.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 460.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 920.0f);

    pattern_->ChangeIndex(0, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 460.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 920.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 1380.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 1840.0f);

    pattern_->ChangeIndex(4, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -1840.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -1380.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -920.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -460.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 0.0f);
}

/**
 * @tc.name: CheckSwiperModelNG001
 * @tc.desc: Test function about SwiperModelNG
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestTwoNg, CheckSwiperModelNG001, TestSize.Level1)
{
    /**
     * @tc.cases: Set indicator type to DIGIT and  BIND mode.
     * @tc.expected: call functions and check the result
     */
    SwiperDigitalParameters swiperDigitalParameters;
    swiperDigitalParameters.dimEnd = std::make_optional(Dimension(10.0f));
    SwiperModelNG swiperModel;
    frameNode_ = swiperModel.CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    EXPECT_NE(frameNode_, nullptr);
    FrameNode* frameNode = static_cast<FrameNode*>(Referenced::RawPtr(frameNode_));
    swiperModel.SetBindIndicator(frameNode, true);
    swiperModel.SetIndicatorType(frameNode, SwiperIndicatorType::DIGIT);
    swiperModel.SetDigitIndicatorStyle(frameNode, swiperDigitalParameters);
    swiperModel.SetCachedCount(frameNode, 2);
    swiperModel.SetLoop(frameNode, false);
    swiperModel.SetIndex(frameNode, 0);
    swiperModel.SetDirection(frameNode, OHOS::Ace::Axis::HORIZONTAL);
    swiperModel.SetAutoPlay(frameNode, false);
    swiperModel.SetDigitIndicatorStyle(frameNode, swiperDigitalParameters);
    swiperModel.SetIndicatorIsBoolean(frameNode, true);
    swiperModel.SetIsIndicatorCustomSize(frameNode, true);
    ViewAbstract::SetWidth(CalcLength(SWIPER_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SWIPER_HEIGHT));
    pattern_ = frameNode_->GetPattern<SwiperPattern>();
    EXPECT_EQ(swiperModel.GetCachedCount(frameNode), 2);
    EXPECT_EQ(swiperModel.GetIndicatorType(frameNode), static_cast<int32_t>(SwiperIndicatorType::DIGIT));
    EXPECT_EQ(swiperModel.GetLoop(frameNode), false);
    EXPECT_EQ(swiperModel.GetIndex(frameNode), 0);
    EXPECT_EQ(swiperModel.GetDirection(frameNode), OHOS::Ace::Axis::HORIZONTAL);
    EXPECT_EQ(swiperModel.GetAutoPlay(frameNode), false);
    EXPECT_EQ(indicatorNode_, nullptr);
    IndicatorModelNG model;
    model.Create();
    auto indicatorNode_ = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    auto controller = indicatorPattern->GetIndicatorController();
    ASSERT_NE(controller, nullptr);
    controller->SetSwiperNode(frameNode_);
    EXPECT_EQ(indicatorPattern->GetNonAutoLayoutDirection(), TextDirection::LTR);
    auto overlongDotIndicatorPaintMethod = indicatorPattern->CreateOverlongDotIndicatorPaintMethod(pattern_);
    EXPECT_NE(overlongDotIndicatorPaintMethod, nullptr);
    auto indicatorPaintMethod = indicatorPattern->CreateDotIndicatorPaintMethodInSingleMode();
    EXPECT_NE(indicatorPaintMethod, nullptr);
    indicatorPattern->OnModifyDone();
    auto dotIndicatorPaintMethod = indicatorPattern->CreateDotIndicatorPaintMethod(pattern_);
    EXPECT_NE(dotIndicatorPaintMethod, nullptr);
    overlongDotIndicatorPaintMethod = indicatorPattern->CreateOverlongDotIndicatorPaintMethod(pattern_);
    EXPECT_NE(overlongDotIndicatorPaintMethod, nullptr);
}

/**
 * @tc.name: CheckSwiperModelNG002
 * @tc.desc: Test function about SwiperModelNG
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestTwoNg, CheckSwiperModelNG002, TestSize.Level1)
{
    /**
     * @tc.cases: Set indicator type to DOT and  BIND mode.
     * @tc.expected: call functions and check the result
     */
    int32_t currentIndex = 0;
    auto onChange = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };
    SwiperParameters swiperParameters;
    SwiperModelNG swiperModel;
    frameNode_ = swiperModel.CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    EXPECT_NE(frameNode_, nullptr);
    FrameNode* frameNode = static_cast<FrameNode*>(Referenced::RawPtr(frameNode_));
    swiperModel.SetBindIndicator(frameNode, true);
    swiperModel.SetIndicatorType(frameNode, SwiperIndicatorType::DOT);
    swiperModel.SetDotIndicatorStyle(frameNode, swiperParameters);
    swiperModel.SetDuration(frameNode, 10);
    swiperModel.ResetDisplayCount(frameNode);
    swiperModel.SetDisplayCount(frameNode, 2);
    swiperModel.SetAutoPlayInterval(frameNode, 10);
    swiperModel.SetDisableSwipe(frameNode, false);
    swiperModel.SetItemSpace(frameNode, Dimension { 10.f });
    swiperModel.SetShowIndicator(frameNode, false);
    swiperModel.SetDisplayArrow(frameNode, false);
    swiperModel.SetEdgeEffect(frameNode, EdgeEffect::SPRING);
    swiperModel.SetNestedScroll(frameNode, 0);
    swiperModel.SetSwiperToIndex(frameNode, 1, false);
    swiperModel.SetIndicatorInteractive(frameNode, true);
    swiperModel.SetOnChange(frameNode, onChange);
    ViewAbstract::SetWidth(CalcLength(SWIPER_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SWIPER_HEIGHT));
    pattern_ = frameNode_->GetPattern<SwiperPattern>();
    controller_ = pattern_->GetSwiperController();
    SwiperMarginOptions marginOptions;
    swiperModel.GetPreviousMargin(frameNode, 1, &marginOptions);
    swiperModel.GetNextMargin(frameNode, 2, &marginOptions);
    RefPtr<Curve> curve = Curves::LINEAR;
    swiperModel.SetCurve(frameNode, curve);
    EXPECT_EQ(swiperModel.GetDuration(frameNode), 10);
    EXPECT_EQ(swiperModel.GetDisplayCount(frameNode), 2);
    EXPECT_EQ(swiperModel.GetAutoPlayInterval(frameNode), 10);
    EXPECT_EQ(swiperModel.GetDisableSwipe(frameNode), false);
    EXPECT_EQ(swiperModel.GetItemSpace(frameNode), 10.0f);
    EXPECT_EQ(swiperModel.GetShowIndicator(frameNode), false);
    EXPECT_EQ(swiperModel.GetShowDisplayArrow(frameNode), 0);
    EXPECT_EQ(swiperModel.GetEffectMode(frameNode), EdgeEffect::SPRING);
}

/**
 * @tc.name: CreateDotWithResourceObj001
 * @tc.desc: Test Swiper Model CreateDotWithResourceObj
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestTwoNg, CreateDotWithResourceObj001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    auto layoutProperty = frameNode->GetLayoutProperty<SwiperLayoutProperty>();
    auto paintProperty = frameNode->GetPaintProperty<SwiperPaintProperty>();

    SwiperParameters swiperParameters;
    swiperParameters.colorVal = Color(Color::BLUE);
    model.CreateDotWithResourceObj(frameNode, swiperParameters);
    model.SetIndicatorStyle(swiperParameters);
    EXPECT_EQ(pattern->swiperParameters_->colorVal, swiperParameters.colorVal);
}
} // namespace OHOS::Ace::NG
