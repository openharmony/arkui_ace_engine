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
namespace {
constexpr int32_t DEFAULT_ITEMS = 8;
constexpr int32_t SWIPER_TO_ONE = 1;
constexpr int32_t SWIPER_TO_TWO = 2;
constexpr int32_t SWIPER_TO_THREE = 3;
constexpr int32_t SWIPER_TO_SEVEN = 7;
} // namespace

class SwiperControllerTestNg : public SwiperTestNg {
public:
    void CreateForEachSwiper(int32_t itemNumber = ITEM_NUMBER);
    void CreateItemsInLazyForEach(int32_t itemNumber = ITEM_NUMBER);
};


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

class SwiperItemMockLazy : public Framework::MockLazyForEachBuilder {
public:
    explicit SwiperItemMockLazy(int32_t itemCnt) : itemCnt_(itemCnt) {}

protected:
    int32_t OnGetTotalCount() override
    {
        return itemCnt_;
    }

    std::pair<std::string, RefPtr<NG::UINode>> OnGetChildByIndex(
        int32_t index, std::unordered_map<std::string, NG::LazyForEachCacheChild>& expiringItems) override
    {
        ButtonModelNG buttonModelNG;
        buttonModelNG.CreateWithLabel("label");
        auto node = ViewStackProcessor::GetInstance()->Finish();
        return { std::to_string(index), node };
    }

private:
    int32_t itemCnt_ = 0;
};

void SwiperControllerTestNg::CreateItemsInLazyForEach(int32_t itemNumber)
{
    RefPtr<LazyForEachActuator> mockLazy = AceType::MakeRefPtr<SwiperItemMockLazy>(itemNumber);
    LazyForEachModelNG lazyForEachModelNG;
    lazyForEachModelNG.Create(mockLazy);
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

    ShowNext();
    EXPECT_TRUE(CurrentIndex(0));

    ShowPrevious();
    EXPECT_TRUE(CurrentIndex(0));

    ChangeIndex(1, false);
    EXPECT_TRUE(CurrentIndex(0));

    ChangeIndex(1, true);
    EXPECT_TRUE(CurrentIndex(0));
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

    ShowNext();
    EXPECT_TRUE(CurrentIndex(0));

    ShowPrevious();
    EXPECT_TRUE(CurrentIndex(0));

    ChangeIndex(1, false);
    EXPECT_TRUE(CurrentIndex(0));

    ChangeIndex(1, true);
    EXPECT_TRUE(CurrentIndex(0));
}

/**
 * @tc.name: ShowNextShowPreviousChangeIndex003
 * @tc.desc: Test ShowNext/ShowPrevious/ChangeIndex Layout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, ShowNextShowPreviousChangeIndex003, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();

    ShowNext();
    EXPECT_TRUE(CurrentIndex(1));

    ShowPrevious();
    EXPECT_TRUE(CurrentIndex(0));

    ChangeIndex(3, false);
    EXPECT_TRUE(CurrentIndex(3));

    ChangeIndex(1, true);
    EXPECT_TRUE(CurrentIndex(1));
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
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();

    GetChildLayoutProperty<ButtonLayoutProperty>(frameNode_, 1)->UpdateVisibility(VisibleType::INVISIBLE);
    GetChildLayoutProperty<ButtonLayoutProperty>(frameNode_, 2)->UpdateVisibility(VisibleType::GONE);
    FlushUITasks();

    /**
     * @tc.steps: step2. Call ShowNext
     * @tc.expected: Show next page, include INVISIBLE/GONE page
     */
    ShowNext();
    EXPECT_TRUE(CurrentIndex(1));
    ShowNext();
    EXPECT_TRUE(CurrentIndex(2));
    ShowNext();
    EXPECT_TRUE(CurrentIndex(3));
    ShowNext();
    EXPECT_TRUE(CurrentIndex(0)); // because of loop, equal to index:0

    /**
     * @tc.steps: step3. Call ShowPrevious
     * @tc.expected: Show ShowPrevious page, include INVISIBLE/GONE page
     */
    ShowPrevious();
    EXPECT_TRUE(CurrentIndex(3));
    ShowPrevious();
    EXPECT_TRUE(CurrentIndex(2));
    ShowPrevious();
    EXPECT_TRUE(CurrentIndex(1));
    ShowPrevious();
    EXPECT_TRUE(CurrentIndex(0));

    /**
     * @tc.steps: step4. Call ChangeIndex without animation
     * @tc.expected: Show ChangeIndex page, include INVISIBLE/GONE page
     */
    ChangeIndex(0, false);
    EXPECT_TRUE(CurrentIndex(0)); // same index
    ChangeIndex(1, false);
    EXPECT_TRUE(CurrentIndex(1));
    ChangeIndex(3, false);
    EXPECT_TRUE(CurrentIndex(3));
    ChangeIndex(-1, false);
    EXPECT_TRUE(CurrentIndex(0)); // invalid index
    ChangeIndex(100, false);
    EXPECT_TRUE(CurrentIndex(0)); // invalid index
    // with animation
    ChangeIndex(1, true);
    EXPECT_TRUE(CurrentIndex(1));
    ChangeIndex(3, true);
    EXPECT_TRUE(CurrentIndex(3));
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
    ShowNext();
    EXPECT_TRUE(CurrentIndex(1));
    ShowNext();
    EXPECT_TRUE(CurrentIndex(2));
    ShowNext();
    EXPECT_TRUE(CurrentIndex(3));
    ShowNext();
    EXPECT_TRUE(CurrentIndex(3));

    /**
     * @tc.steps: step3. Call ShowPrevious
     * @tc.expected: Show ShowPrevious page
     */
    ShowPrevious();
    EXPECT_TRUE(CurrentIndex(2));
    ShowPrevious();
    EXPECT_TRUE(CurrentIndex(1));
    ShowPrevious();
    EXPECT_TRUE(CurrentIndex(0));
    ShowPrevious();
    EXPECT_TRUE(CurrentIndex(0));

    /**
     * @tc.steps: step4. Call ChangeIndex without animation
     * @tc.expected: Show ChangeIndex page
     */
    ChangeIndex(1, false);
    EXPECT_TRUE(CurrentIndex(1));
    ChangeIndex(3, false);
    EXPECT_TRUE(CurrentIndex(3));
    // with animation
    ChangeIndex(1, true);
    EXPECT_TRUE(CurrentIndex(1));
    ChangeIndex(3, true);
    EXPECT_TRUE(CurrentIndex(3));
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
    FlushUITasks();

    /**
     * @tc.steps: step2. Call ShowNext
     * @tc.expected: Show next page, include INVISIBLE/GONE page
     */
    ShowNext();
    EXPECT_TRUE(CurrentIndex(1));
    ShowNext();
    EXPECT_TRUE(CurrentIndex(2));
    ShowNext();
    EXPECT_TRUE(CurrentIndex(3));
    ShowNext();
    EXPECT_TRUE(CurrentIndex(0)); // because of loop, equal to index:0

    /**
     * @tc.steps: step3. Call ShowPrevious
     * @tc.expected: Show ShowPrevious page, include INVISIBLE/GONE page
     */
    ShowPrevious();
    EXPECT_TRUE(CurrentIndex(3));
    ShowPrevious();
    EXPECT_TRUE(CurrentIndex(2));
    ShowPrevious();
    EXPECT_TRUE(CurrentIndex(1));
    ShowPrevious();
    EXPECT_TRUE(CurrentIndex(0));

    /**
     * @tc.steps: step4. Call ChangeIndex without animation
     * @tc.expected: Show ChangeIndex page, include INVISIBLE/GONE page
     */
    ChangeIndex(1, false);
    EXPECT_TRUE(CurrentIndex(1));
    ChangeIndex(3, false);
    EXPECT_TRUE(CurrentIndex(3));
    // with animation
    ChangeIndex(1, true);
    EXPECT_TRUE(CurrentIndex(1));
    ChangeIndex(3, true);
    EXPECT_TRUE(CurrentIndex(3));
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
    ShowNext();
    EXPECT_TRUE(CurrentIndex(3));
    ShowNext();
    EXPECT_TRUE(CurrentIndex(0)); // because of loop, equal to index:0

    /**
     * @tc.steps: step3. Call ShowPrevious
     * @tc.expected: Show ShowPrevious page
     */
    ShowPrevious();
    EXPECT_TRUE(CurrentIndex(3));
    ShowPrevious();
    EXPECT_TRUE(CurrentIndex(0));

    /**
     * @tc.steps: step4. Call ChangeIndex
     * @tc.expected: Show ChangeIndex page
     */
    ChangeIndex(3, false);
    EXPECT_TRUE(CurrentIndex(3));
    ChangeIndex(3, true);
    EXPECT_TRUE(CurrentIndex(3));
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
    ShowNext();
    EXPECT_TRUE(CurrentIndex(1));

    /**
     * @tc.steps: step3. Call ShowPrevious
     * @tc.expected: Show ShowPrevious page
     */
    ShowPrevious();
    EXPECT_TRUE(CurrentIndex(0));

    /**
     * @tc.steps: step4. Call ChangeIndex
     * @tc.expected: Show ChangeIndex page
     */
    ChangeIndex(0, false);
    EXPECT_TRUE(CurrentIndex(0));
    // expect 0
    ChangeIndex(2, false);
    EXPECT_TRUE(CurrentIndex(1));
    // expect 0
    ChangeIndex(3, false);
    EXPECT_TRUE(CurrentIndex(1));
    ChangeIndex(0, true);
    EXPECT_TRUE(CurrentIndex(0));
    // expect 0
    ChangeIndex(2, true);
    EXPECT_TRUE(CurrentIndex(1));
    // expect 0
    ChangeIndex(3, true);
    EXPECT_TRUE(CurrentIndex(1));
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
    ShowNext();
    EXPECT_TRUE(CurrentIndex(0));

    /**
     * @tc.steps: step3. Call ShowPrevious
     * @tc.expected: Show ShowPrevious page
     */
    ShowPrevious();
    EXPECT_TRUE(CurrentIndex(0));

    /**
     * @tc.steps: step4. Call ChangeIndex
     * @tc.expected: Show ChangeIndex page
     */
    // expect 0
    ChangeIndex(0, false);
    EXPECT_TRUE(CurrentIndex(0));
    // expect 0
    ChangeIndex(2, false);
    EXPECT_TRUE(CurrentIndex(0));
    // expect 0
    ChangeIndex(0, true);
    EXPECT_TRUE(CurrentIndex(0));
    // expect 0
    ChangeIndex(3, true);
    EXPECT_TRUE(CurrentIndex(0));
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
    FlushUITasks();

    /**
     * @tc.steps: step3. Call ShowNext
     * @tc.expected: Show next item(index:1)
     */
    ShowNext();
    EXPECT_TRUE(CurrentIndex(1));

    /**
     * @tc.steps: step4. Call ShowNext
     * @tc.expected: Show item(index:3) because item(index:2) is GONE
     */
    ShowNext();
    EXPECT_TRUE(CurrentIndex(3));
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
    FlushUITasks();

    /**
     * @tc.steps: step3. Call ShowNext
     * @tc.expected: Show next item(index:1)
     */
    ShowNext();
    EXPECT_TRUE(CurrentIndex(1));

    /**
     * @tc.steps: step4. Call ShowNext
     * @tc.expected: Show item(index:3) because item(index:2) is GONE
     */
    ShowNext();
    EXPECT_TRUE(CurrentIndex(3));

    /**
     * @tc.steps: step4. Call ShowNext
     * @tc.expected: Show item(index:3) because loop:false
     */
    ShowNext();
    EXPECT_TRUE(CurrentIndex(3));
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
    EXPECT_TRUE(CurrentIndex(3));

    /**
     * @tc.steps: step2. Set item(index:1,2) visibility:false
     * @tc.expected: item(index:1,2) still place, have two page
     */
    GetChildLayoutProperty<ButtonLayoutProperty>(frameNode_, 1)->UpdateVisibility(VisibleType::INVISIBLE);
    GetChildLayoutProperty<ButtonLayoutProperty>(frameNode_, 2)->UpdateVisibility(VisibleType::GONE);
    FlushUITasks();

    /**
     * @tc.steps: step3. Call ShowPrevious
     * @tc.expected: Show pre item(index:1) because item(index:2) is GONE
     */
    ShowPrevious();
    EXPECT_TRUE(CurrentIndex(1));

    /**
     * @tc.steps: step4. Call ShowPrevious
     * @tc.expected: Show pre item
     */
    ShowPrevious();
    EXPECT_TRUE(CurrentIndex(0));
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
    FlushUITasks();

    /**
     * @tc.steps: step3. Call ShowPrevious
     * @tc.expected: Show pre item(index:1) because item(index:2) is GONE
     */
    ShowPrevious();
    EXPECT_TRUE(CurrentIndex(1));

    /**
     * @tc.steps: step4. Call ShowPrevious
     * @tc.expected: Show pre item
     */
    ShowPrevious();
    EXPECT_TRUE(CurrentIndex(0));

    /**
     * @tc.steps: step4. Call ShowPrevious
     * @tc.expected: Show item(index:0) because loop:false
     */
    ShowPrevious();
    EXPECT_TRUE(CurrentIndex(0));
}

/**
 * @tc.name: FinishAnimation001
 * @tc.desc: Test SwiperController func
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, FinishAnimation001, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();

    /**
     * @tc.steps: step1. Call FinishAnimation
     * @tc.expected: Animation stoped
     */
    pattern_->translateAnimationIsRunning_ = true;
    controller_->FinishAnimation();
    EXPECT_FALSE(pattern_->translateAnimationIsRunning_);
    EXPECT_TRUE(pattern_->isUserFinish_);
    EXPECT_FALSE(pattern_->isFinishAnimation_);

    pattern_->propertyAnimationIsRunning_ = true;
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
    FlushUITasks();
    auto forEachNode = AceType::DynamicCast<ForEachNode>(frameNode_->GetChildAtIndex(0));
    EXPECT_EQ(forEachNode->TotalChildCount(), 4);
}

/**
 * @tc.name: PreloadItems002
 * @tc.desc: Test LazyForEach
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, PreloadItems002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetCachedCount(1);
    CreateItemsInLazyForEach();
    CreateSwiperDone();

    PipelineContext::GetCurrentContext()->OnIdle(INT64_MAX);
    EXPECT_TRUE(IsExistAndActive(frameNode_, 0));
    EXPECT_TRUE(IsExistAndInActive(frameNode_, 1));
    EXPECT_FALSE(IsExist(frameNode_, 2));
    EXPECT_TRUE(IsExistAndInActive(frameNode_, 3));

    ShowNext();
    PipelineContext::GetCurrentContext()->OnIdle(INT64_MAX);
    EXPECT_TRUE(IsExistAndInActive(frameNode_, 0));
    EXPECT_TRUE(IsExistAndActive(frameNode_, 1));
    EXPECT_TRUE(IsExistAndInActive(frameNode_, 2));
    EXPECT_FALSE(IsExist(frameNode_, 3));

    ShowNext();
    PipelineContext::GetCurrentContext()->OnIdle(INT64_MAX);
    EXPECT_FALSE(IsExist(frameNode_, 0));
    EXPECT_TRUE(IsExistAndInActive(frameNode_, 1));
    EXPECT_TRUE(IsExistAndActive(frameNode_, 2));
    EXPECT_TRUE(IsExistAndInActive(frameNode_, 3));

    ShowPrevious();
    PipelineContext::GetCurrentContext()->OnIdle(INT64_MAX);
    EXPECT_TRUE(IsExistAndInActive(frameNode_, 0));
    EXPECT_TRUE(IsExistAndActive(frameNode_, 1));
    EXPECT_TRUE(IsExistAndInActive(frameNode_, 2));
    EXPECT_FALSE(IsExist(frameNode_, 3));

    ShowPrevious();
    PipelineContext::GetCurrentContext()->OnIdle(INT64_MAX);
    EXPECT_TRUE(IsExistAndActive(frameNode_, 0));
    EXPECT_TRUE(IsExistAndInActive(frameNode_, 1));
    EXPECT_FALSE(IsExist(frameNode_, 2));
    EXPECT_TRUE(IsExistAndInActive(frameNode_, 3));

    ChangeIndex(2);
    PipelineContext::GetCurrentContext()->OnIdle(INT64_MAX);
    EXPECT_FALSE(IsExist(frameNode_, 0));
    EXPECT_TRUE(IsExistAndInActive(frameNode_, 1));
    EXPECT_TRUE(IsExistAndActive(frameNode_, 2));
    EXPECT_TRUE(IsExistAndInActive(frameNode_, 3));
}

/**
 * @tc.name: PreloadItems003
 * @tc.desc: Test LazyForEach with SwipeByGroup
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, PreloadItems003, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetCachedCount(1);
    model.SetDisplayCount(2);
    model.SetSwipeByGroup(true);
    CreateItemsInLazyForEach(8);
    CreateSwiperDone();

    PipelineContext::GetCurrentContext()->OnIdle(INT64_MAX);
    EXPECT_TRUE(IsExistAndActive(frameNode_, 0));
    EXPECT_TRUE(IsExistAndActive(frameNode_, 1));
    EXPECT_TRUE(IsExistAndInActive(frameNode_, 2));
    EXPECT_TRUE(IsExistAndInActive(frameNode_, 3));
    EXPECT_FALSE(IsExist(frameNode_, 4));
    EXPECT_FALSE(IsExist(frameNode_, 5));
    EXPECT_TRUE(IsExistAndInActive(frameNode_, 6));
    EXPECT_TRUE(IsExistAndInActive(frameNode_, 7));

    ShowNext();
    PipelineContext::GetCurrentContext()->OnIdle(INT64_MAX);
    EXPECT_TRUE(IsExistAndInActive(frameNode_, 0));
    EXPECT_TRUE(IsExistAndInActive(frameNode_, 1));
    EXPECT_TRUE(IsExistAndActive(frameNode_, 2));
    EXPECT_TRUE(IsExistAndActive(frameNode_, 3));
    EXPECT_TRUE(IsExistAndInActive(frameNode_, 4));
    EXPECT_TRUE(IsExistAndInActive(frameNode_, 5));
    EXPECT_FALSE(IsExist(frameNode_, 6));
    EXPECT_FALSE(IsExist(frameNode_, 7));

    ShowNext();
    PipelineContext::GetCurrentContext()->OnIdle(INT64_MAX);
    EXPECT_FALSE(IsExist(frameNode_, 0));
    EXPECT_FALSE(IsExist(frameNode_, 1));
    EXPECT_TRUE(IsExistAndInActive(frameNode_, 2));
    EXPECT_TRUE(IsExistAndInActive(frameNode_, 3));
    EXPECT_TRUE(IsExistAndActive(frameNode_, 4));
    EXPECT_TRUE(IsExistAndActive(frameNode_, 5));
    EXPECT_TRUE(IsExistAndInActive(frameNode_, 6));
    EXPECT_TRUE(IsExistAndInActive(frameNode_, 7));

    ShowPrevious();
    PipelineContext::GetCurrentContext()->OnIdle(INT64_MAX);
    EXPECT_TRUE(IsExistAndInActive(frameNode_, 0));
    EXPECT_TRUE(IsExistAndInActive(frameNode_, 1));
    EXPECT_TRUE(IsExistAndActive(frameNode_, 2));
    EXPECT_TRUE(IsExistAndActive(frameNode_, 3));
    EXPECT_TRUE(IsExistAndInActive(frameNode_, 4));
    EXPECT_TRUE(IsExistAndInActive(frameNode_, 5));
    EXPECT_FALSE(IsExist(frameNode_, 6));
    EXPECT_FALSE(IsExist(frameNode_, 7));

    ShowPrevious();
    PipelineContext::GetCurrentContext()->OnIdle(INT64_MAX);
    EXPECT_TRUE(IsExistAndActive(frameNode_, 0));
    EXPECT_TRUE(IsExistAndActive(frameNode_, 1));
    EXPECT_TRUE(IsExistAndInActive(frameNode_, 2));
    EXPECT_TRUE(IsExistAndInActive(frameNode_, 3));
    EXPECT_FALSE(IsExist(frameNode_, 4));
    EXPECT_FALSE(IsExist(frameNode_, 5));
    EXPECT_TRUE(IsExistAndInActive(frameNode_, 6));
    EXPECT_TRUE(IsExistAndInActive(frameNode_, 7));

    ChangeIndex(4);
    PipelineContext::GetCurrentContext()->OnIdle(INT64_MAX);
    EXPECT_FALSE(IsExist(frameNode_, 0));
    EXPECT_FALSE(IsExist(frameNode_, 1));
    EXPECT_TRUE(IsExistAndInActive(frameNode_, 2));
    EXPECT_TRUE(IsExistAndInActive(frameNode_, 3));
    EXPECT_TRUE(IsExistAndActive(frameNode_, 4));
    EXPECT_TRUE(IsExistAndActive(frameNode_, 5));
    EXPECT_TRUE(IsExistAndInActive(frameNode_, 6));
    EXPECT_TRUE(IsExistAndInActive(frameNode_, 7));
}

/**
 * @tc.name: LazyForEachRequestLongPredict001
 * @tc.desc: Test LazyForEach requestLongPredict_
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, LazyForEachNeedPredict001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateItemsInLazyForEach();
    CreateSwiperDone();
    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(frameNode_->GetChildAtIndex(0));
    EXPECT_TRUE(lazyForEachNode->requestLongPredict_);
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
    FlushUITasks();

    ChangeIndex(2, false);
    EXPECT_TRUE(CurrentIndex(3));
    ChangeIndex(5, false);
    EXPECT_TRUE(CurrentIndex(5));
    ChangeIndex(2, false);
    EXPECT_TRUE(CurrentIndex(1));
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

    ChangeIndex(9, false);
    EXPECT_TRUE(CurrentIndex(9));
}

/**
 * @tc.name: ChangeIndex003
 * @tc.desc: Test ChangeIndex with animation and without animation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, ChangeIndex003, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    CreateSwiperItems(8);
    CreateSwiperDone();

    ChangeIndex(3, true);
    EXPECT_TRUE(CurrentIndex(3));
    ChangeIndex(1, false);
    EXPECT_TRUE(CurrentIndex(1));
}

/**
 * @tc.name: ChangeIndex004
 * @tc.desc: Test ChangeIndex with SwiperAnimationMode
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, ChangeIndex004, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    CreateSwiperItems(DEFAULT_ITEMS);
    CreateSwiperDone();

    ChangeIndex(SWIPER_TO_THREE, SwiperAnimationMode::NO_ANIMATION);
    EXPECT_TRUE(CurrentIndex(SWIPER_TO_THREE));
    ChangeIndex(SWIPER_TO_ONE, SwiperAnimationMode::NO_ANIMATION);
    EXPECT_TRUE(CurrentIndex(SWIPER_TO_ONE));
    ChangeIndex(SWIPER_TO_THREE, SwiperAnimationMode::DEFAULT_ANIMATION);
    EXPECT_TRUE(CurrentIndex(SWIPER_TO_THREE));
    ChangeIndex(SWIPER_TO_ONE, SwiperAnimationMode::DEFAULT_ANIMATION);
    EXPECT_TRUE(CurrentIndex(SWIPER_TO_ONE));
    ChangeIndex(SWIPER_TO_SEVEN, SwiperAnimationMode::FAST_ANIMATION);
    EXPECT_TRUE(CurrentIndex(SWIPER_TO_SEVEN));
    ChangeIndex(SWIPER_TO_ONE, SwiperAnimationMode::FAST_ANIMATION);
    EXPECT_TRUE(CurrentIndex(SWIPER_TO_ONE));
    ChangeIndex(SWIPER_TO_TWO, SwiperAnimationMode::FAST_ANIMATION);
    EXPECT_TRUE(CurrentIndex(SWIPER_TO_TWO));
    ChangeIndex(SWIPER_TO_ONE, SwiperAnimationMode::FAST_ANIMATION);
    EXPECT_TRUE(CurrentIndex(SWIPER_TO_ONE));
}

/**
 * @tc.name: ChangeIndexWithLoopChange001
 * @tc.desc: Test changeIndex with loop change
 * @tc.type: FUNC
 */
HWTEST_F(SwiperControllerTestNg, ChangeIndexWithLoopChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. loop is false, ShowPrevious
     * @tc.expected: current index is -1
     */
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    model.SetPreviousMargin(Dimension(PRE_MARGIN), false);
    CreateSwiperItems();
    CreateSwiperDone();
    ShowPrevious();
    EXPECT_TRUE(CurrentIndex(3));

    /**
     * @tc.steps: step2. ChangeIndex and loop changes to true
     * @tc.expected: current index change to 1
     */
    controller_->ChangeIndex(1, false);
    layoutProperty_->UpdateLoop(false);
    pattern_->OnModifyDone();
    FlushUITasks();
    EXPECT_TRUE(CurrentIndex(1));
}
} // namespace OHOS::Ace::NG
