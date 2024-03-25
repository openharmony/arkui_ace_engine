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
};

/**
 * @tc.name: ShowNext001
 * @tc.desc: Test SwiperController func
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, ShowNext001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. SetIndex:3
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetIndex(3);
    });

    /**
     * @tc.steps: step2. Set item(index:1) INVISIBLE
     */
    auto itemLayoutProperty1 = GetChildLayoutProperty<TextLayoutProperty>(frameNode_, 1);
    itemLayoutProperty1->UpdateVisibility(VisibleType::INVISIBLE);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step3. Call ShowNext
     * @tc.expected: Show first page because of loop
     */
    controller_->ShowNext();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 0);
    
    /**
     * @tc.steps: step4. Call ShowNext
     * @tc.expected: Show next page
     */
    controller_->ShowNext();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 1);
}

/**
 * @tc.name: ShowNext002
 * @tc.desc: Test SwiperController func
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, ShowNext002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set loop:false, index:3
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetLoop(false);
        model.SetIndex(3);
    });

    /**
     * @tc.steps: step2. Call ShowNext
     * @tc.expected: Show last page because is not loop
     */
    controller_->ShowNext();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 3);
}

/**
 * @tc.name: ShowNext003
 * @tc.desc: Test SwiperController func
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, ShowNext003, TestSize.Level1)
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
    auto itemLayoutProperty1 = GetChildLayoutProperty<TextLayoutProperty>(frameNode_, 1);
    auto itemLayoutProperty2 = GetChildLayoutProperty<TextLayoutProperty>(frameNode_, 2);
    itemLayoutProperty1->UpdateVisibility(VisibleType::INVISIBLE);
    itemLayoutProperty2->UpdateVisibility(VisibleType::GONE);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step3. Call ShowNext
     * @tc.expected: Show next page
     */
    controller_->ShowNext();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 1);

    /**
     * @tc.steps: step4. Call ShowNext
     * @tc.expected: Show first page because of loop
     */
    controller_->ShowNext();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 2);
}

/**
 * @tc.name: ShowNext004
 * @tc.desc: Test SwiperController func
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
    controller_->ShowNext();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 3);

    /**
     * @tc.steps: step2. Call ShowNext
     * @tc.expected: Show first page because of loop
     */
    controller_->ShowNext();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 3);
}

/**
 * @tc.name: ShowPrevious001
 * @tc.desc: Test SwiperController func
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, ShowPrevious001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});

    /**
     * @tc.steps: step1. Call ShowPrevious
     * @tc.expected: Show last page because of loop
     */
    controller_->ShowPrevious();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 3);

    /**
     * @tc.steps: step2. Call ShowPrevious
     * @tc.expected: Show pre page
     */
    controller_->ShowPrevious();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 2);
}

/**
 * @tc.name: ShowPrevious002
 * @tc.desc: Test SwiperController func
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
     * @tc.expected: Show first page because is not loop
     */
    controller_->ShowPrevious();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 0);
}

/**
 * @tc.name: ShowPrevious003
 * @tc.desc: Test SwiperController func
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
    auto itemLayoutProperty1 = GetChildLayoutProperty<TextLayoutProperty>(frameNode_, 1);
    auto itemLayoutProperty2 = GetChildLayoutProperty<TextLayoutProperty>(frameNode_, 2);
    itemLayoutProperty1->UpdateVisibility(VisibleType::INVISIBLE);
    itemLayoutProperty2->UpdateVisibility(VisibleType::GONE);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step3. Call ShowPrevious
     * @tc.expected: Show last page because of loop
     */
    controller_->ShowPrevious();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 3);

    /**
     * @tc.steps: step4. Call ShowPrevious
     * @tc.expected: Show pre page
     */
    controller_->ShowPrevious();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 2);
}

/**
 * @tc.name: ShowPrevious004
 * @tc.desc: Test SwiperController func
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
    controller_->ShowPrevious();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 3);

    /**
     * @tc.steps: step2. Call ShowPrevious
     * @tc.expected: Show pre page
     */
    controller_->ShowPrevious();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 0);
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
 * @tc.desc: Test SwiperController func
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, ChangeIndex001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});

    /**
     * @tc.steps: step1. Call ChangeIndex without useAnimation
     */
    controller_->ChangeIndex(1, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 1);

    /**
     * @tc.steps: step2. Call ChangeIndex with useAnimation
     */
    controller_->ChangeIndex(3, true);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 3);
}
} // namespace OHOS::Ace::NG
