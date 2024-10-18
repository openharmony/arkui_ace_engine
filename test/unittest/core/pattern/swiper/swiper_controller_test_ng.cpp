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
#include "test/unittest/core/syntax/mock_lazy_for_each_actuator.h"
#include "test/unittest/core/syntax/mock_lazy_for_each_builder.h"

#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_model_ng.h"
#include "core/components_ng/syntax/for_each_model_ng.h"
#include "core/components_ng/syntax/for_each_node.h"
#include "core/components_ng/syntax/lazy_for_each_model_ng.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"
#include "core/components_ng/syntax/lazy_layout_wrapper_builder.h"
#include "core/components_ng/syntax/syntax_item.h"

namespace OHOS::Ace::NG {
class SwiperControllerTestNg : public SwiperTestNg {
public:
    AssertionResult VerifyShowNext(int32_t expectIndex);
    AssertionResult VerifyShowPrevious(int32_t expectIndex);
    AssertionResult VerifyChangeIndex(int32_t targetIndex, bool useAnimation, int32_t expectIndex);
    void CreateForEachSwiper(int32_t itemNumber = ITEM_NUMBER);
    void CreateLazyForEachSwiper(int32_t itemNumber = ITEM_NUMBER);
};

AssertionResult SwiperControllerTestNg::VerifyShowNext(int32_t expectIndex)
{
    controller_->ShowNext();
    FlushLayoutTask(frameNode_);
    return IsEqual(pattern_->GetCurrentShownIndex(), expectIndex);
}

AssertionResult SwiperControllerTestNg::VerifyShowPrevious(int32_t expectIndex)
{
    controller_->ShowPrevious();
    FlushLayoutTask(frameNode_);
    return IsEqual(pattern_->GetCurrentShownIndex(), expectIndex);
}

AssertionResult SwiperControllerTestNg::VerifyChangeIndex(int32_t targetIndex, bool useAnimation, int32_t expectIndex)
{
    controller_->ChangeIndex(targetIndex, useAnimation);
    FlushLayoutTask(frameNode_);
    return IsEqual(pattern_->GetCurrentShownIndex(), expectIndex);
}

void SwiperControllerTestNg::CreateForEachSwiper(int32_t itemNumber)
{
    SwiperModelNG model = CreateSwiper();
    model.SetIndicatorType(SwiperIndicatorType::DOT);
    auto swiperNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto weakSwiper = AceType::WeakClaim(AceType::RawPtr(swiperNode));
    ForEachModelNG forEachModelNG;
    forEachModelNG.Create();
    auto forEachNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    forEachNode->SetParent(weakSwiper); // for InitAllChildrenDragManager
    std::list<std::string> newIds;
    for (int32_t index = 0; index < itemNumber; index++) {
        newIds.emplace_back(std::to_string(index));
    }
    forEachModelNG.SetNewIds(std::move(newIds));
    for (int32_t index = 0; index < itemNumber; index++) {
        // key is 0,1,2,3...
        forEachModelNG.CreateNewChildStart(std::to_string(index));
        CreateSwiperItems(1);
        forEachModelNG.CreateNewChildFinish(std::to_string(index));
    }
    CreateSwiperDone();
}

void SwiperControllerTestNg::CreateLazyForEachSwiper(int32_t itemNumber)
{
    SwiperModelNG model = CreateSwiper();
    model.SetIndicatorType(SwiperIndicatorType::DOT);
    auto swiperNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto weakSwiper = AceType::WeakClaim(AceType::RawPtr(swiperNode));
    const RefPtr<LazyForEachActuator> lazyForEachActuator = AceType::MakeRefPtr<Framework::MockLazyForEachBuilder>();
    LazyForEachModelNG lazyForEachModelNG;
    lazyForEachModelNG.Create(lazyForEachActuator);
    auto node = ViewStackProcessor::GetInstance()->GetMainElementNode();
    node->SetParent(weakSwiper); // for InitAllChildrenDragManager
    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(node);
    for (int32_t index = 0; index < itemNumber; index++) {
        ButtonModelNG buttonModelNG;
        buttonModelNG.CreateWithLabel("label");
        auto swiperItemNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
        lazyForEachNode->builder_->cachedItems_.try_emplace(
            index, LazyForEachChild(std::to_string(index), swiperItemNode));
        ViewStackProcessor::GetInstance()->Pop();
    }
    CreateSwiperDone();
}

/**
 * @tc.name: ShowNextShowPreviousChangeIndex001
 * @tc.desc: Test ShowPrevious with no items, can not swipe
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, ShowNextShowPreviousChangeIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Empty items
     * @tc.expected: Can not swipe
     */
    CreateSwiper();
    CreateSwiperDone();
    EXPECT_TRUE(VerifyShowNext(0));
    EXPECT_TRUE(VerifyShowPrevious(0));
    EXPECT_TRUE(VerifyChangeIndex(1, false, 0));
    EXPECT_TRUE(VerifyChangeIndex(1, true, 0));
}

/**
 * @tc.name: ShowNextShowPreviousChangeIndex002
 * @tc.desc: Test ShowNext with DisplayCount bigger than total items
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, ShowNextShowPreviousChangeIndex002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set DisplayCount(5) > totalItems(4)
     * @tc.expected: Can not swipe
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(ITEM_NUMBER + 1);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_TRUE(VerifyShowNext(0));
    EXPECT_TRUE(VerifyShowPrevious(0));
    EXPECT_TRUE(VerifyChangeIndex(1, false, 0));
    EXPECT_TRUE(VerifyChangeIndex(1, true, 0));
}

/**
 * @tc.name: ShowNextShowPreviousChangeIndex003
 * @tc.desc: Test ShowNext/ShowPrevious/ChangeIndex Layout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, ShowNextShowPreviousChangeIndex003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Swiper, set isVisibleArea_:false for without animation
     */
    CreateDefaultSwiper();
    pattern_->isVisibleArea_ = false; // for without animation

    /**
     * @tc.steps: step2. Call ShowNext
     * @tc.expected: Show next page
     */
    EXPECT_TRUE(VerifyShowNext(1));
    EXPECT_EQ(GetChildX(frameNode_, 1), 0.f);
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 1)->IsActive());

    /**
     * @tc.steps: step3. Call ShowPrevious
     * @tc.expected: Show ShowPrevious page
     */
    EXPECT_TRUE(VerifyShowPrevious(0));
    EXPECT_EQ(GetChildX(frameNode_, 0), 0.f);
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 1)->IsActive());
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 0)->IsActive());

    /**
     * @tc.steps: step4. Call ChangeIndex without animation
     * @tc.expected: Show ChangeIndex page
     */
    EXPECT_TRUE(VerifyChangeIndex(3, false, 3));
    EXPECT_EQ(GetChildX(frameNode_, 3), 0.f);
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 0)->IsActive());
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 3)->IsActive());
}

/**
 * @tc.name: ShowNextShowPreviousChangeIndex004
 * @tc.desc: Test ShowNext/ShowPrevious/ChangeIndex with loop:true and invisible/gone items
 * will show first item when ShowNext from last item, the invisible/gone item still take a place
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, ShowNextShowPreviousChangeIndex004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Loop default is true, Set item(index:1,2) INVISIBLE and GONE
     * @tc.expected: The item still take a place
     */
    CreateDefaultSwiper();
    GetChildLayoutProperty<ButtonLayoutProperty>(frameNode_, 1)->UpdateVisibility(VisibleType::INVISIBLE);
    GetChildLayoutProperty<ButtonLayoutProperty>(frameNode_, 2)->UpdateVisibility(VisibleType::GONE);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call ShowNext
     * @tc.expected: Show next page, include INVISIBLE/GONE page
     */
    EXPECT_TRUE(VerifyShowNext(1));
    EXPECT_TRUE(VerifyShowNext(2));
    EXPECT_TRUE(VerifyShowNext(3));
    EXPECT_TRUE(VerifyShowNext(4)); // because of loop, equal to index:0

    /**
     * @tc.steps: step3. Call ShowPrevious
     * @tc.expected: Show ShowPrevious page, include INVISIBLE/GONE page
     */
    EXPECT_TRUE(VerifyShowPrevious(3));
    EXPECT_TRUE(VerifyShowPrevious(2));
    EXPECT_TRUE(VerifyShowPrevious(1));
    EXPECT_TRUE(VerifyShowPrevious(0));

    /**
     * @tc.steps: step4. Call ChangeIndex without animation
     * @tc.expected: Show ChangeIndex page, include INVISIBLE/GONE page
     */
    EXPECT_TRUE(VerifyChangeIndex(0, false, 0)); // same index
    EXPECT_TRUE(VerifyChangeIndex(1, false, 1));
    EXPECT_TRUE(VerifyChangeIndex(3, false, 3));
    EXPECT_TRUE(VerifyChangeIndex(-1, false, 0));  // invalid index
    EXPECT_TRUE(VerifyChangeIndex(100, false, 0)); // invalid index
    // with animation
    EXPECT_TRUE(VerifyChangeIndex(1, true, 1));
    EXPECT_TRUE(VerifyChangeIndex(3, true, 3));
}

/**
 * @tc.name: ShowNextShowPreviousChangeIndex005
 * @tc.desc: Test ShowNext/ShowPrevious/ChangeIndex with loop:false,
 * will still show last item when ShowNext from last item
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, ShowNextShowPreviousChangeIndex005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set loop:false
     */
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    CreateSwiperItems();
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Call ShowNext
     * @tc.expected: Show next page
     */
    EXPECT_TRUE(VerifyShowNext(1));
    EXPECT_TRUE(VerifyShowNext(2));
    EXPECT_TRUE(VerifyShowNext(3));
    EXPECT_TRUE(VerifyShowNext(3));

    /**
     * @tc.steps: step3. Call ShowPrevious
     * @tc.expected: Show ShowPrevious page
     */
    EXPECT_TRUE(VerifyShowPrevious(2));
    EXPECT_TRUE(VerifyShowPrevious(1));
    EXPECT_TRUE(VerifyShowPrevious(0));
    EXPECT_TRUE(VerifyShowPrevious(0));

    /**
     * @tc.steps: step4. Call ChangeIndex without animation
     * @tc.expected: Show ChangeIndex page
     */
    EXPECT_TRUE(VerifyChangeIndex(1, false, 1));
    EXPECT_TRUE(VerifyChangeIndex(3, false, 3));
    // with animation
    EXPECT_TRUE(VerifyChangeIndex(1, true, 1));
    EXPECT_TRUE(VerifyChangeIndex(3, true, 3));
}

/**
 * @tc.name: ShowNextShowPreviousChangeIndex006
 * @tc.desc: Test ShowNext/ShowPrevious/ChangeIndex with DisplayCount,
 * the gone item not take a place, but still exist page
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, ShowNextShowPreviousChangeIndex006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set DisplayCount:3
     * @tc.expected: Has 3 items in 1 page
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(3);
    CreateSwiperItems();
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Set item(index:1,2) visibility:false
     * @tc.expected: item(index:1,2) still place, have two page
     */
    GetChildLayoutProperty<ButtonLayoutProperty>(frameNode_, 1)->UpdateVisibility(VisibleType::INVISIBLE);
    GetChildLayoutProperty<ButtonLayoutProperty>(frameNode_, 2)->UpdateVisibility(VisibleType::GONE);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call ShowNext
     * @tc.expected: Show next page, include INVISIBLE/GONE page
     */
    EXPECT_TRUE(VerifyShowNext(1));
    EXPECT_TRUE(VerifyShowNext(2));
    EXPECT_TRUE(VerifyShowNext(3));
    EXPECT_TRUE(VerifyShowNext(4)); // because of loop, equal to index:0

    /**
     * @tc.steps: step3. Call ShowPrevious
     * @tc.expected: Show ShowPrevious page, include INVISIBLE/GONE page
     */
    EXPECT_TRUE(VerifyShowPrevious(3));
    EXPECT_TRUE(VerifyShowPrevious(2));
    EXPECT_TRUE(VerifyShowPrevious(1));
    EXPECT_TRUE(VerifyShowPrevious(0));

    /**
     * @tc.steps: step4. Call ChangeIndex without animation
     * @tc.expected: Show ChangeIndex page, include INVISIBLE/GONE page
     */
    EXPECT_TRUE(VerifyChangeIndex(1, false, 1));
    EXPECT_TRUE(VerifyChangeIndex(3, false, 3));
    // with animation
    EXPECT_TRUE(VerifyChangeIndex(1, true, 1));
    EXPECT_TRUE(VerifyChangeIndex(3, true, 3));
}

/**
 * @tc.name: ShowNextShowPreviousChangeIndex007
 * @tc.desc: Test ShowNext/ShowPrevious/ChangeIndex with DisplayCount and SwipeByGroup
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, ShowNextShowPreviousChangeIndex007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set DisplayCount:3, SwipeByGroup:true
     * @tc.expected: Has 3 items in 1 page and SwipeByGroup
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(3);
    model.SetSwipeByGroup(true);
    CreateSwiperItems();
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Call ShowNext
     * @tc.expected: Show next page
     */
    EXPECT_TRUE(VerifyShowNext(3));
    EXPECT_TRUE(VerifyShowNext(6)); // because of loop, equal to index:0

    /**
     * @tc.steps: step3. Call ShowPrevious
     * @tc.expected: Show ShowPrevious page
     */
    EXPECT_TRUE(VerifyShowPrevious(3));
    EXPECT_TRUE(VerifyShowPrevious(0));

    /**
     * @tc.steps: step4. Call ChangeIndex
     * @tc.expected: Show ChangeIndex page
     */
    EXPECT_TRUE(VerifyChangeIndex(3, false, 3));
    EXPECT_TRUE(VerifyChangeIndex(3, true, 3));
}

/**
 * @tc.name: ShowNextShowPreviousChangeIndex008
 * @tc.desc: Test ShowNext/ShowPrevious/ChangeIndex with next/pre margin
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, ShowNextShowPreviousChangeIndex008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set DisplayCount:3
     */
    const float preMargin = 10.f;
    const float nextMargin = 20.f;
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetDisplayCount(3);
    model.SetPreviousMargin(Dimension(preMargin), true);
    model.SetNextMargin(Dimension(nextMargin), true);
    CreateSwiperItems();
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Call ShowNext
     * @tc.expected: Show next page
     */
    EXPECT_TRUE(VerifyShowNext(1));

    /**
     * @tc.steps: step3. Call ShowPrevious
     * @tc.expected: Show ShowPrevious page
     */
    EXPECT_TRUE(VerifyShowPrevious(0));

    /**
     * @tc.steps: step4. Call ChangeIndex
     * @tc.expected: Show ChangeIndex page
     */
    EXPECT_TRUE(VerifyChangeIndex(0, false, 0));
    // expect 0
    EXPECT_TRUE(VerifyChangeIndex(2, false, 1));
    // expect 0
    EXPECT_TRUE(VerifyChangeIndex(3, false, 1));
    EXPECT_TRUE(VerifyChangeIndex(0, true, 0));
    // expect 0
    EXPECT_TRUE(VerifyChangeIndex(2, true, 1));
    // expect 0
    EXPECT_TRUE(VerifyChangeIndex(3, true, 1));
}

/**
 * @tc.name: ShowNextShowPreviousChangeIndex009
 * @tc.desc: Test ShowNext/ShowPrevious/ChangeIndex with next/pre margin
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, ShowNextShowPreviousChangeIndex009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set DisplayCount:10 over itemCount
     */
    const float preMargin = 10.f;
    const float nextMargin = 20.f;
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetDisplayCount(10);
    model.SetPreviousMargin(Dimension(preMargin), true);
    model.SetNextMargin(Dimension(nextMargin), true);
    CreateSwiperItems();
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Call ShowNext
     * @tc.expected: Show next page
     */
    EXPECT_TRUE(VerifyShowNext(0));

    /**
     * @tc.steps: step3. Call ShowPrevious
     * @tc.expected: Show ShowPrevious page
     */
    EXPECT_TRUE(VerifyShowPrevious(0));

    /**
     * @tc.steps: step4. Call ChangeIndex
     * @tc.expected: Show ChangeIndex page
     */
    // expect 0
    EXPECT_TRUE(VerifyChangeIndex(0, false, 0));
    // expect 0
    EXPECT_TRUE(VerifyChangeIndex(2, false, 0));
    // expect 0
    EXPECT_TRUE(VerifyChangeIndex(0, true, 0));
    // expect 0
    EXPECT_TRUE(VerifyChangeIndex(3, true, 0));
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
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    CreateItemWithSize(200.f, SWIPER_HEIGHT);
    CreateItemWithSize(300.f, SWIPER_HEIGHT);
    CreateItemWithSize(400.f, SWIPER_HEIGHT);
    CreateItemWithSize(500.f, SWIPER_HEIGHT);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Set item(index:1,2) visibility:false
     * @tc.expected: item(index:1,2) still place, have two page
     */
    GetChildLayoutProperty<ButtonLayoutProperty>(frameNode_, 1)->UpdateVisibility(VisibleType::INVISIBLE);
    GetChildLayoutProperty<ButtonLayoutProperty>(frameNode_, 2)->UpdateVisibility(VisibleType::GONE);
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
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    CreateItemWithSize(200.f, SWIPER_HEIGHT);
    CreateItemWithSize(300.f, SWIPER_HEIGHT);
    CreateItemWithSize(400.f, SWIPER_HEIGHT);
    CreateItemWithSize(500.f, SWIPER_HEIGHT);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Set item(index:1,2) visibility:false
     * @tc.expected: item(index:1,2) still place, have two page
     */
    GetChildLayoutProperty<ButtonLayoutProperty>(frameNode_, 1)->UpdateVisibility(VisibleType::INVISIBLE);
    GetChildLayoutProperty<ButtonLayoutProperty>(frameNode_, 2)->UpdateVisibility(VisibleType::GONE);
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
 * @tc.name: ShowPrevious005
 * @tc.desc: Test ShowPrevious with SwiperDisplayMode::AUTO_LINEAR, swipe distance by the item width in the view
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, ShowPrevious005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set AUTO_LINEAR, create diff item width
     */
    SwiperModelNG model = CreateSwiper();
    model.SetIndex(3);
    model.SetDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    CreateItemWithSize(200.f, SWIPER_HEIGHT);
    CreateItemWithSize(300.f, SWIPER_HEIGHT);
    CreateItemWithSize(400.f, SWIPER_HEIGHT);
    CreateItemWithSize(500.f, SWIPER_HEIGHT);
    CreateSwiperDone();
    EXPECT_EQ(pattern_->GetCurrentShownIndex(), 3);

    /**
     * @tc.steps: step2. Set item(index:1,2) visibility:false
     * @tc.expected: item(index:1,2) still place, have two page
     */
    GetChildLayoutProperty<ButtonLayoutProperty>(frameNode_, 1)->UpdateVisibility(VisibleType::INVISIBLE);
    GetChildLayoutProperty<ButtonLayoutProperty>(frameNode_, 2)->UpdateVisibility(VisibleType::GONE);
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
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetIndex(3);
    model.SetDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    CreateItemWithSize(200.f, SWIPER_HEIGHT);
    CreateItemWithSize(300.f, SWIPER_HEIGHT);
    CreateItemWithSize(400.f, SWIPER_HEIGHT);
    CreateItemWithSize(500.f, SWIPER_HEIGHT);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Set item(index:1,2) visibility:false
     * @tc.expected: item(index:1,2) still place, have two page
     */
    GetChildLayoutProperty<ButtonLayoutProperty>(frameNode_, 1)->UpdateVisibility(VisibleType::INVISIBLE);
    GetChildLayoutProperty<ButtonLayoutProperty>(frameNode_, 2)->UpdateVisibility(VisibleType::GONE);
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
 * @tc.name: FinishAnimation001
 * @tc.desc: Test SwiperController func
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, FinishAnimation001, TestSize.Level1)
{
    CreateDefaultSwiper();

    /**
     * @tc.steps: step1. Call FinishAnimation
     * @tc.expected: Animation stoped
     */
    pattern_->translateAnimationIsRunning_ = true;
    controller_->FinishAnimation();
    EXPECT_FALSE(pattern_->translateAnimationIsRunning_);
    EXPECT_TRUE(pattern_->isUserFinish_);
    EXPECT_FALSE(pattern_->isFinishAnimation_);

    pattern_->usePropertyAnimation_ = true;
    controller_->SetFinishCallback([]() {});
    controller_->FinishAnimation();
    EXPECT_EQ(controller_->GetFinishCallback(), nullptr);
    EXPECT_FALSE(pattern_->isFinishAnimation_);
}

/**
 * @tc.name: PreloadItems001
 * @tc.desc: Test SwiperPattern ChangeIndex On SwipeByGroup
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, PreloadItems001, TestSize.Level1)
{
    CreateForEachSwiper();
    const std::set<int32_t>& indexSet = { 1, 2 };
    controller_->PreloadItems(indexSet);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(frameNode_);
    auto forEachNode = AceType::DynamicCast<ForEachNode>(frameNode_->GetChildAtIndex(0));
    EXPECT_EQ(forEachNode->TotalChildCount(), 4);
}

/**
 * @tc.name: PreloadItems002
 * @tc.desc: Test SwiperPattern ChangeIndex On SwipeByGroup
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, PreloadItems002, TestSize.Level1)
{
    CreateLazyForEachSwiper();
    const std::set<int32_t>& indexSet = { 1, 2 };
    controller_->PreloadItems(indexSet);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(frameNode_->TotalChildCount(), 5);
}

/**
 * @tc.name: ChangeIndex001
 * @tc.desc: Test ChangeIndex with SwiperDisplayMode::AUTO_LINEAR and item invisible
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, ChangeIndex001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetIndex(0);
    model.SetDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    CreateItemWithSize(200.f, SWIPER_HEIGHT);
    CreateItemWithSize(300.f, SWIPER_HEIGHT);
    CreateItemWithSize(400.f, SWIPER_HEIGHT);
    CreateItemWithSize(500.f, SWIPER_HEIGHT);
    CreateItemWithSize(100.f, SWIPER_HEIGHT);
    CreateItemWithSize(100.f, SWIPER_HEIGHT);
    CreateSwiperDone();

    GetChildLayoutProperty<ButtonLayoutProperty>(frameNode_, 2)->UpdateVisibility(VisibleType::GONE);
    FlushLayoutTask(frameNode_);

    VerifyChangeIndex(2, false, 3);
    VerifyChangeIndex(5, false, 5);
    VerifyChangeIndex(2, false, 1);
}

/**
 * @tc.name: ChangeIndex002
 * @tc.desc: Test ChangeIndex with prevMargin nextMargin itemSpace
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, ChangeIndex002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetPreviousMargin(Dimension(20), false);
    model.SetNextMargin(Dimension(20), false);
    model.SetItemSpace(Dimension(30));
    model.SetDisplayCount(3);
    CreateSwiperItems(10);
    CreateSwiperDone();

    VerifyChangeIndex(9, false, 9);
}
} // namespace OHOS::Ace::NG
