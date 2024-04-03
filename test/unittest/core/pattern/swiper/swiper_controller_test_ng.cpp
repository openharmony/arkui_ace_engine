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
} // namespace OHOS::Ace::NG
