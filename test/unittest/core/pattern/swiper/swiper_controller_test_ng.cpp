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

namespace OHOS::Ace::NG {

namespace {} // namespace

class SwiperControllerTestNg : public SwiperTestNg {
public:
    AssertionResult VerifyShowNext(int32_t expectIndex);
    AssertionResult VerifyShowPrevious(int32_t expectIndex);
};

AssertionResult SwiperControllerTestNg::VerifyShowNext(int32_t expectIndex)
{
    controller_->ShowNext();
    FlushLayoutTask(frameNode_);
    return IsEqual(pattern_->GetCurrentIndex(), expectIndex);
}

AssertionResult SwiperControllerTestNg::VerifyShowPrevious(int32_t expectIndex)
{
    controller_->ShowPrevious();
    FlushLayoutTask(frameNode_);
    return IsEqual(pattern_->GetCurrentIndex(), expectIndex);
}

/**
 * @tc.name: ShowNext001
 * @tc.desc: Test ShowNext with loop:true and invisible/gone items
 * will show first item when ShowNext from last item, the invisible/gone item still take a place
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, ShowNext001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. SetIndex:3(last item), loop default is true
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetIndex(3);
    });

    /**
     * @tc.steps: step2. Set item(index:1,2) INVISIBLE and GONE
     * @tc.expected: The item still take a place
     */
    GetChildLayoutProperty<TextLayoutProperty>(frameNode_, 1)->UpdateVisibility(VisibleType::INVISIBLE);
    GetChildLayoutProperty<TextLayoutProperty>(frameNode_, 2)->UpdateVisibility(VisibleType::GONE);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step3. Call ShowNext
     * @tc.expected: Show first page because of loop
     */
    EXPECT_TRUE(VerifyShowNext(0));

    /**
     * @tc.steps: step4. Call ShowNext
     * @tc.expected: Show next page(INVISIBLE item)
     */
    EXPECT_TRUE(VerifyShowNext(1));

    /**
     * @tc.steps: step5. Call ShowNext
     * @tc.expected: Show next page(GONE item)
     */
    EXPECT_TRUE(VerifyShowNext(2));
}

/**
 * @tc.name: ShowNext002
 * @tc.desc: Test ShowNext with loop:false, will still show last item when ShowNext from last item
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, ShowNext002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set loop:false, index:3(last item)
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetLoop(false);
        model.SetIndex(3);
    });
    EXPECT_EQ(pattern_->GetCurrentIndex(), 3);

    /**
     * @tc.steps: step2. Call ShowNext
     * @tc.expected: Show last page because loop is false
     */
    EXPECT_TRUE(VerifyShowNext(3));
}

/**
 * @tc.name: ShowNext003
 * @tc.desc: Test ShowNext with DisplayCount, the gone item not take a place, but still exist page
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, ShowNext003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set DisplayCount:3, set index:1
     * @tc.expected: Has 3 items in 1 page
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetIndex(1);
        model.SetDisplayCount(3);
    });
    EXPECT_EQ(pattern_->GetCurrentIndex(), 1);

    /**
     * @tc.steps: step2. Set item(index:1,2) visibility:false
     * @tc.expected: item(index:1,2) still place, have two page
     */
    GetChildLayoutProperty<TextLayoutProperty>(frameNode_, 1)->UpdateVisibility(VisibleType::INVISIBLE);
    GetChildLayoutProperty<TextLayoutProperty>(frameNode_, 2)->UpdateVisibility(VisibleType::GONE);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step3. Call ShowNext
     * @tc.expected: Show next item in first page
     */
    EXPECT_TRUE(VerifyShowNext(2));

    /**
     * @tc.steps: step4. Call ShowNext
     * @tc.expected: Show next item in second page
     */
    EXPECT_TRUE(VerifyShowNext(3));

    /**
     * @tc.steps: step5. Call ShowNext
     * @tc.expected: Show first item in first page because of loop
     */
    EXPECT_TRUE(VerifyShowNext(0));
}

/**
 * @tc.name: ShowNext004
 * @tc.desc: Test ShowNext with DisplayCount and SwipeByGroup
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, ShowNext004, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayCount(3);
        model.SetSwipeByGroup(true);
    });

    /**
     * @tc.steps: step1. Call ShowNext
     * @tc.expected: Show next page
     */
    EXPECT_TRUE(VerifyShowNext(3));

    /**
     * @tc.steps: step2. Call ShowNext
     * @tc.expected: Show first page because of loop
     */
    EXPECT_TRUE(VerifyShowNext(0));
}

/**
 * @tc.name: ShowNext005
 * @tc.desc: Test ShowNext with SwiperDisplayMode::AUTO_LINEAR, swipe distance by the item width in the view
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, ShowNext005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set AUTO_LINEAR, create diff item width
     */
    Create([](SwiperModelNG model) {
        model.SetDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
        CreateItemWithSize(200.f, SWIPER_HEIGHT);
        CreateItemWithSize(300.f, SWIPER_HEIGHT);
        CreateItemWithSize(400.f, SWIPER_HEIGHT);
        CreateItemWithSize(500.f, SWIPER_HEIGHT);
    });

    /**
     * @tc.steps: step2. Set item(index:1,2) visibility:false
     * @tc.expected: item(index:1,2) still place, have two page
     */
    GetChildLayoutProperty<TextLayoutProperty>(frameNode_, 1)->UpdateVisibility(VisibleType::INVISIBLE);
    GetChildLayoutProperty<TextLayoutProperty>(frameNode_, 2)->UpdateVisibility(VisibleType::GONE);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step3. Call ShowNext
     * @tc.expected: Show next item(index:1)
     */
    EXPECT_TRUE(VerifyShowNext(1));

    /**
     * @tc.steps: step4. Call ShowNext
     * @tc.expected: Show item(index:3) because item(index:2) is GONE
     */
    EXPECT_TRUE(VerifyShowNext(3));
}

/**
 * @tc.name: ShowNext006
 * @tc.desc: Test ShowNext with SwiperDisplayMode::AUTO_LINEAR and loop:false,
 * swipe distance by the item width in the view
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, ShowNext006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set AUTO_LINEAR, create diff item width
     */
    Create([](SwiperModelNG model) {
        model.SetLoop(false);
        model.SetDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
        CreateItemWithSize(200.f, SWIPER_HEIGHT);
        CreateItemWithSize(300.f, SWIPER_HEIGHT);
        CreateItemWithSize(400.f, SWIPER_HEIGHT);
        CreateItemWithSize(500.f, SWIPER_HEIGHT);
    });

    /**
     * @tc.steps: step2. Set item(index:1,2) visibility:false
     * @tc.expected: item(index:1,2) still place, have two page
     */
    GetChildLayoutProperty<TextLayoutProperty>(frameNode_, 1)->UpdateVisibility(VisibleType::INVISIBLE);
    GetChildLayoutProperty<TextLayoutProperty>(frameNode_, 2)->UpdateVisibility(VisibleType::GONE);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step3. Call ShowNext
     * @tc.expected: Show next item(index:1)
     */
    EXPECT_TRUE(VerifyShowNext(1));

    /**
     * @tc.steps: step4. Call ShowNext
     * @tc.expected: Show item(index:3) because item(index:2) is GONE
     */
    EXPECT_TRUE(VerifyShowNext(3));

    /**
     * @tc.steps: step4. Call ShowNext
     * @tc.expected: Show item(index:3) because loop:false
     */
    EXPECT_TRUE(VerifyShowNext(3));
}

/**
 * @tc.name: ShowPrevious001
 * @tc.desc: Test ShowPrevious with loop:true and invisible/gone items
 * will show last item when ShowPrevious from first item, the invisible/gone item still take a place
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, ShowPrevious001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});

    /**
     * @tc.steps: step1. Set item(index:1) INVISIBLE
     */
    GetChildLayoutProperty<TextLayoutProperty>(frameNode_, 2)->UpdateVisibility(VisibleType::INVISIBLE);
    GetChildLayoutProperty<TextLayoutProperty>(frameNode_, 1)->UpdateVisibility(VisibleType::GONE);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call ShowPrevious
     * @tc.expected: Show last page because of loop
     */
    EXPECT_TRUE(VerifyShowPrevious(3));

    /**
     * @tc.steps: step3. Call ShowPrevious
     * @tc.expected: Show pre page
     */
    EXPECT_TRUE(VerifyShowPrevious(2));

    /**
     * @tc.steps: step4. Call ShowPrevious
     * @tc.expected: Show pre page
     */
    EXPECT_TRUE(VerifyShowPrevious(1));
}

/**
 * @tc.name: ShowPrevious002
 * @tc.desc: Test ShowPrevious with loop:false, will still show first item when ShowPrevious from first item
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, ShowPrevious002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set loop:false
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetLoop(false);
    });

    /**
     * @tc.steps: step2. Call ShowPrevious
     * @tc.expected: Show first page because loop is false
     */
    EXPECT_TRUE(VerifyShowPrevious(0));
}

/**
 * @tc.name: ShowPrevious003
 * @tc.desc: Test ShowPrevious with DisplayCount, the gone item not take a place, but still exist page
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, ShowPrevious003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. SetDisplayCount
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayCount(3);
    });

    /**
     * @tc.steps: step2. Set item(index:1,2) visibility:false
     * @tc.expected: item(index:1,2) still place, have two page
     */
    GetChildLayoutProperty<TextLayoutProperty>(frameNode_, 1)->UpdateVisibility(VisibleType::INVISIBLE);
    GetChildLayoutProperty<TextLayoutProperty>(frameNode_, 2)->UpdateVisibility(VisibleType::GONE);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step3. Call ShowPrevious
     * @tc.expected: Show last page in second page because of loop
     */
    EXPECT_TRUE(VerifyShowPrevious(3));

    /**
     * @tc.steps: step4. Call ShowPrevious
     * @tc.expected: Show pre page in first page
     */
    EXPECT_TRUE(VerifyShowPrevious(2));

    /**
     * @tc.steps: step5. Call ShowPrevious
     * @tc.expected: Show pre page in first page
     */
    EXPECT_TRUE(VerifyShowPrevious(1));
}

/**
 * @tc.name: ShowPrevious004
 * @tc.desc: Test ShowPrevious with DisplayCount and SwipeByGroup
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, ShowPrevious004, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayCount(3);
        model.SetSwipeByGroup(true);
    });

    /**
     * @tc.steps: step1. Call ShowPrevious
     * @tc.expected: Show last page because of loop
     */
    EXPECT_TRUE(VerifyShowPrevious(3));

    /**
     * @tc.steps: step2. Call ShowPrevious
     * @tc.expected: Show pre page
     */
    EXPECT_TRUE(VerifyShowPrevious(0));
}

/**
 * @tc.name: ShowPrevious005
 * @tc.desc: Test ShowPrevious with SwiperDisplayMode::AUTO_LINEAR, swipe distance by the item width in the view
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, ShowPrevious005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set AUTO_LINEAR, create diff item width
     */
    Create([](SwiperModelNG model) {
        model.SetIndex(3);
        model.SetDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
        CreateItemWithSize(200.f, SWIPER_HEIGHT);
        CreateItemWithSize(300.f, SWIPER_HEIGHT);
        CreateItemWithSize(400.f, SWIPER_HEIGHT);
        CreateItemWithSize(500.f, SWIPER_HEIGHT);
    });
    EXPECT_EQ(pattern_->GetCurrentIndex(), 3);

    /**
     * @tc.steps: step2. Set item(index:1,2) visibility:false
     * @tc.expected: item(index:1,2) still place, have two page
     */
    GetChildLayoutProperty<TextLayoutProperty>(frameNode_, 1)->UpdateVisibility(VisibleType::INVISIBLE);
    GetChildLayoutProperty<TextLayoutProperty>(frameNode_, 2)->UpdateVisibility(VisibleType::GONE);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step3. Call ShowPrevious
     * @tc.expected: Show pre item(index:1) because item(index:2) is GONE
     */
    EXPECT_TRUE(VerifyShowPrevious(1));

    /**
     * @tc.steps: step4. Call ShowPrevious
     * @tc.expected: Show pre item
     */
    EXPECT_TRUE(VerifyShowPrevious(0));
}

/**
 * @tc.name: ShowPrevious006
 * @tc.desc: Test ShowPrevious with SwiperDisplayMode::AUTO_LINEAR and loop:false,
 * swipe distance by the item width in the view
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, ShowPrevious006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set AUTO_LINEAR, create diff item width
     */
    Create([](SwiperModelNG model) {
        model.SetLoop(false);
        model.SetIndex(3);
        model.SetDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
        CreateItemWithSize(200.f, SWIPER_HEIGHT);
        CreateItemWithSize(300.f, SWIPER_HEIGHT);
        CreateItemWithSize(400.f, SWIPER_HEIGHT);
        CreateItemWithSize(500.f, SWIPER_HEIGHT);
    });

    /**
     * @tc.steps: step2. Set item(index:1,2) visibility:false
     * @tc.expected: item(index:1,2) still place, have two page
     */
    GetChildLayoutProperty<TextLayoutProperty>(frameNode_, 1)->UpdateVisibility(VisibleType::INVISIBLE);
    GetChildLayoutProperty<TextLayoutProperty>(frameNode_, 2)->UpdateVisibility(VisibleType::GONE);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step3. Call ShowPrevious
     * @tc.expected: Show pre item(index:1) because item(index:2) is GONE
     */
    EXPECT_TRUE(VerifyShowPrevious(1));

    /**
     * @tc.steps: step4. Call ShowPrevious
     * @tc.expected: Show pre item
     */
    EXPECT_TRUE(VerifyShowPrevious(0));

    /**
     * @tc.steps: step4. Call ShowPrevious
     * @tc.expected: Show item(index:0) because loop:false
     */
    EXPECT_TRUE(VerifyShowPrevious(0));
}

/**
 * @tc.name: ShowNextPrevious001
 * @tc.desc: Test ShowPrevious with no items, can not swipe
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, ShowNextPrevious001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call ShowPrevious
     * @tc.expected: Can not swipe
     */
    Create([](SwiperModelNG model) {});
    EXPECT_TRUE(VerifyShowNext(0));
    EXPECT_TRUE(VerifyShowPrevious(0));
}

/**
 * @tc.name: ShowNextPrevious002
 * @tc.desc: Test ShowNext with DisplayCount bigger than total items
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, ShowNextPrevious002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set DisplayCount(5) > totalItems(4)
     * @tc.expected: Can not swipe
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayCount(5);
    });
    EXPECT_TRUE(VerifyShowNext(0));
    EXPECT_TRUE(VerifyShowPrevious(0));
}

/**
 * @tc.name: FinishAnimation001
 * @tc.desc: Test SwiperController func
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, FinishAnimation001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});

    /**
     * @tc.steps: step1. Call FinishAnimation
     * @tc.expected: Animation stoped
     */
    controller_->FinishAnimation();
    EXPECT_TRUE(pattern_->isUserFinish_);
}

/**
 * @tc.name: ChangeIndex001
 * @tc.desc: Test ChangeIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, ChangeIndex001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});

    /**
     * @tc.steps: step1. Call ChangeIndex without useAnimation
     * @tc.expected: Swipe to item(index:1)
     */
    controller_->ChangeIndex(1, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 1);

    /**
     * @tc.steps: step2. Call ChangeIndex without useAnimation again
     * @tc.expected: Still is item(index:1)
     */
    controller_->ChangeIndex(1, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 1);

    /**
     * @tc.steps: step3. Call ChangeIndex with useAnimation
     * @tc.expected: Swipe to item(index:3)
     */
    controller_->ChangeIndex(3, true);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 3);
}

/**
 * @tc.name: ChangeIndex002
 * @tc.desc: Test ChangeIndex invalid args
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, ChangeIndex002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call ChangeIndex ITEM_NUMBER
     * @tc.expected: Can not swipe
     */
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->ChangeIndex(ITEM_NUMBER, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 0);
}

/**
 * @tc.name: ChangeIndex003
 * @tc.desc: Test SwiperPattern ChangeIndex On SwipeByGroup
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, ChangeIndex003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set DisplayCount:3, SwipeByGroup:true
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayCount(3);
        model.SetSwipeByGroup(true);
    });

    /**
     * @tc.steps: step2. Call ChangeIndex:2
     * @tc.expected: Can not swipe
     */
    pattern_->ChangeIndex(2, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 0);

    /**
     * @tc.steps: step2. Call ChangeIndex:3
     * @tc.expected: Swipe to item(index:3)
     */
    pattern_->ChangeIndex(3, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 3);
}

/**
 * @tc.name: SwiperPatternInitSwiperController001
 * @tc.desc: InitSwiperController
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, SwiperPatternInitSwiperController001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->swiperController_->showPrevImpl_ = nullptr;

    /**
     * @tc.steps: step2. call InitSwiperController.
     * @tc.expected: Related function runs ok.
     */
    pattern_->InitSwiperController();
    pattern_->swiperController_->swipeToImpl_(0, true);
    pattern_->swiperController_->swipeToWithoutAnimationImpl_(0);
    pattern_->swiperController_->showNextImpl_();
    pattern_->swiperController_->showPrevImpl_();
    pattern_->swiperController_->changeIndexImpl_(0, true);
    pattern_->swiperController_->finishImpl_();
    std::set<int32_t> indexSet;
    pattern_->swiperController_->preloadItemsImpl_(indexSet);
    indexSet.insert(1);
    pattern_->swiperController_->preloadItemsImpl_(indexSet);
}

/**
 * @tc.name: SwiperPatternChangeIndex001
 * @tc.desc: ChangeIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, SwiperPatternChangeIndex001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});

    pattern_->ChangeIndex(1, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentShownIndex(), 1);
}

/**
 * @tc.name: SwiperPatternChangeIndex002
 * @tc.desc: ChangeIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, SwiperPatternChangeIndex002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});

    pattern_->ChangeIndex(1, true);
    EXPECT_EQ(pattern_->targetIndex_.value_or(0), 1);
}

/**
 * @tc.name: SwiperPatternChangeIndex003
 * @tc.desc: ChangeIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, SwiperPatternChangeIndex003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto totalCount = pattern_->TotalCount();
    EXPECT_EQ(totalCount, 4);

    pattern_->ChangeIndex(4, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentShownIndex(), 0);
}

/**
 * @tc.name: SwiperPatternSwipeByGroupChangeIndex001
 * @tc.desc: Test SwiperPattern ChangeIndex On SwipeByGroup
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, SwiperPatternSwipeByGroupChangeIndex001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto totalCount = pattern_->TotalCount();
    EXPECT_EQ(totalCount, 4);

    layoutProperty_->UpdateSwipeByGroup(true);
    layoutProperty_->UpdateDisplayCount(2);
    layoutProperty_->UpdateLoop(true);
    pattern_->currentIndex_ = 0;
    pattern_->isVisible_ = true;
    pattern_->ChangeIndex(3, true);
    EXPECT_EQ(pattern_->targetIndex_.value_or(0), 2);
}

/**
 * @tc.name: SwiperPatternShowNext001
 * @tc.desc: ShowNext
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, SwiperPatternShowNext001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    ASSERT_EQ(pattern_->TotalCount(), 4);
    layoutProperty_->UpdateLoop(true);
    layoutProperty_->UpdateDisplayCount(-1);
    layoutProperty_->UpdateMinSize(Dimension(-1));
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    pattern_->currentIndex_ = 1;
    pattern_->preTargetIndex_ = -1;
    layoutProperty_->UpdateShowIndicator(false);
    pattern_->leftButtonId_.reset();

    /**
     * @tc.steps: step2. call ShowNext.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->ShowNext();
            if (i == 1) {
                pattern_->preTargetIndex_ = 0;
                ASSERT_EQ(pattern_->GetLoopIndex(pattern_->preTargetIndex_.value()), 0);
                continue;
            }
            pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 2 }));
            pattern_->itemPosition_.emplace(std::make_pair(-3, SwiperItemInfo { 1, 2 }));
            pattern_->preTargetIndex_ = -1;
            EXPECT_EQ(pattern_->TotalCount(), 6);
            EXPECT_EQ(pattern_->GetLoopIndex(pattern_->preTargetIndex_.value()), 5);
        }
        layoutProperty_->UpdateLoop(false);
        ASSERT_FALSE(pattern_->IsLoop());
    }

    pattern_->preTargetIndex_.reset();
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->ShowNext();
            if (i == 1) {
                pattern_->currentIndex_ = 5;
                continue;
            }
            pattern_->currentIndex_ = 1;
        }
        layoutProperty_->UpdateLoop(false);
        ASSERT_FALSE(pattern_->IsLoop());
    }
    layoutProperty_->UpdateLoop(true);
    pattern_->rightButtonId_.reset();
    layoutProperty_->UpdateDisplayCount(1);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->ShowNext();
            if (i == 1) {
                layoutProperty_->UpdateDisplayCount(1);
                continue;
            }
            layoutProperty_->UpdateDisplayCount(0);
        }
        }
    for (int i = 0; i <= 1; i++) {
        pattern_->ShowNext();
        pattern_->isVisible_ = false;
    }
}

/**
 * @tc.name: SwipeByGroupShowNext001
 * @tc.desc: Test SwiperPattern ShowNext On SwipeByGroup
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, SwiperPatternSwipeByGroupShowNext001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto totalCount = pattern_->TotalCount();
    EXPECT_EQ(totalCount, 4);

    layoutProperty_->UpdateSwipeByGroup(true);
    layoutProperty_->UpdateDisplayCount(3);
    layoutProperty_->UpdateLoop(true);
    pattern_->currentIndex_ = 0;
    pattern_->isVisible_ = true;
    pattern_->ShowNext();
    EXPECT_EQ(pattern_->targetIndex_.value_or(0), 3);
}

/**
 * @tc.name: SwipeByGroupShowPrevious001
 * @tc.desc: Test SwiperPattern ShowPrevious On SwipeByGroup
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, SwiperPatternSwipeByGroupShowPrevious001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto totalCount = pattern_->TotalCount();
    EXPECT_EQ(totalCount, 4);

    layoutProperty_->UpdateSwipeByGroup(true);
    layoutProperty_->UpdateDisplayCount(3);
    layoutProperty_->UpdateLoop(true);
    pattern_->currentIndex_ = 0;
    pattern_->isVisible_ = true;
    pattern_->ShowPrevious();
    EXPECT_EQ(pattern_->targetIndex_.value_or(0), -3);
}

/**
 * @tc.name: SwiperPatternShowPrevious001
 * @tc.desc: ShowPrevious
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, SwiperPatternShowPrevious001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    layoutProperty_->UpdateShowIndicator(false);
    pattern_->currentIndex_ = 0;
    pattern_->preTargetIndex_ = -1;

    layoutProperty_->UpdateLoop(true);
    layoutProperty_->UpdateDisplayCount(-3);
    layoutProperty_->UpdateMinSize(Dimension(-1));
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    EXPECT_EQ(pattern_->TotalDisPlayCount(), 1);
    EXPECT_TRUE(pattern_->IsLoop());

    /**
     * @tc.steps: step2. call ShowPrevious.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->ShowPrevious();
            if (i == 1) {
                pattern_->preTargetIndex_ = 0;
                ASSERT_EQ(pattern_->GetLoopIndex(pattern_->preTargetIndex_.value()), 0);
                continue;
            }
            pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 2 }));
            pattern_->itemPosition_.emplace(std::make_pair(-3, SwiperItemInfo { 1, 2 }));
            pattern_->preTargetIndex_ = 1;
            EXPECT_EQ(pattern_->GetLoopIndex(pattern_->preTargetIndex_.value()), 1);
        }
        layoutProperty_->UpdateLoop(false);
        ASSERT_FALSE(pattern_->IsLoop());
    }

    pattern_->preTargetIndex_.reset();
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->ShowPrevious();
            if (i == 1) {
                pattern_->currentIndex_ = 1;
                continue;
            }
            pattern_->currentIndex_ = 0;
        }
        layoutProperty_->UpdateLoop(false);
        ASSERT_FALSE(pattern_->IsLoop());
    }

    pattern_->preTargetIndex_ = 1;
    layoutProperty_->UpdateLoop(true);
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateDisplayCount(1);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->ShowPrevious();
            pattern_->preTargetIndex_.reset();
        }
        pattern_->isVisible_ = false;
    }

    layoutProperty_->UpdateLoop(true);
    pattern_->rightButtonId_.reset();
    pattern_->leftButtonId_.reset();
    layoutProperty_->UpdateDisplayCount(1);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->ShowPrevious();
            if (i == 1) {
                layoutProperty_->UpdateDisplayCount(1);
                continue;
            }
            layoutProperty_->UpdateDisplayCount(0);
        }
        }
}

/**
 * @tc.name: SwiperPatternShowPrevious002
 * @tc.desc: ShowPrevious
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, SwiperPatternShowPrevious002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    layoutProperty_->UpdateShowIndicator(false);
    ASSERT_EQ(pattern_->TotalCount(), 5);
    pattern_->currentIndex_ = 0;
    pattern_->preTargetIndex_ = -1;

    layoutProperty_->UpdateLoop(true);
    layoutProperty_->UpdateDisplayCount(-3);
    layoutProperty_->UpdateMinSize(Dimension(-1));
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    EXPECT_EQ(pattern_->TotalDisPlayCount(), 1);
    EXPECT_TRUE(pattern_->IsLoop());
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 2 }));
    pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1, 2 }));

    /**
     * @tc.steps: step2. call ShowPrevious.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->ShowPrevious();
            if (i == 1) {
                layoutProperty_->UpdateDisplayCount(-3);
                continue;
            }
            layoutProperty_->UpdateDisplayCount(0);
        }
        }

    for (int i = 0; i <= 1; i++) {
        pattern_->ShowPrevious();
        pattern_->isVisible_ = false;
        pattern_->preTargetIndex_ = 0;
    }
}

/**
 * @tc.name: SwiperPatternShowPrevious003
 * @tc.desc: ShowPrevious
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, SwiperPatternShowPrevious003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    pattern_->currentIndex_ = 0;
    pattern_->preTargetIndex_ = 1;

    layoutProperty_->UpdateLoop(true);
    layoutProperty_->ResetDisplayCount();
    layoutProperty_->ResetMinSize();
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    layoutProperty_->UpdateShowIndicator(false);
    pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1.0f, 2.0f }));
    pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1.0f, 2.0f }));
    EXPECT_FALSE(pattern_->IsVisibleChildrenSizeLessThanSwiper());
    EXPECT_TRUE(pattern_->preTargetIndex_.has_value());
    EXPECT_TRUE(pattern_->IsLoop());
    EXPECT_EQ(pattern_->TotalCount(), 7);
    EXPECT_EQ(pattern_->GetDisplayCount(), 1);
    pattern_->targetIndex_ = 2;
    EXPECT_FALSE(pattern_->GetLoopIndex(pattern_->preTargetIndex_.value()) <= 0 && !pattern_->IsLoop());
    EXPECT_FALSE(pattern_->IsVisibleChildrenSizeLessThanSwiper());

    /**
     * @tc.steps: step2. call ShowPrevious.
     * @tc.expected: Related function runs ok.
     */
    pattern_->ShowPrevious();
    EXPECT_EQ(pattern_->preTargetIndex_.value(), -1);
    pattern_->isVisible_ = false;
    pattern_->preTargetIndex_ = 0;
    pattern_->isUserFinish_ = true;
    pattern_->ShowPrevious();
    EXPECT_EQ(pattern_->preTargetIndex_.value(), 0);
}
} // namespace OHOS::Ace::NG
