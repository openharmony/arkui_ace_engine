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

#include "list_test_ng.h"
#include "test/mock/core/animation/mock_animation_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

namespace OHOS::Ace::NG {
class ListAttrTestTwoNg : public ListTestNg {};

/**
 * @tc.name: EdgeEffectOption001
 * @tc.desc: Test EdgeEffectOption
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestTwoNg, EdgeEffectOption001, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetEdgeEffect(EdgeEffect::SPRING, false);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    EXPECT_FALSE(pattern_->GetAlwaysEnabled());
    EXPECT_TRUE(pattern_->isScrollable_);
}

/**
 * @tc.name: EdgeEffectOption002
 * @tc.desc: Test EdgeEffectOption
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestTwoNg, EdgeEffectOption002, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    EXPECT_TRUE(pattern_->GetAlwaysEnabled());
    EXPECT_TRUE(pattern_->isScrollable_);
}

/**
 * @tc.name: EdgeEffectOption003
 * @tc.desc: Test EdgeEffectOption
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestTwoNg, EdgeEffectOption003, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetEdgeEffect(EdgeEffect::SPRING, false);
    CreateListItems(1);
    CreateDone();
    EXPECT_FALSE(pattern_->GetAlwaysEnabled());
    EXPECT_FALSE(pattern_->isScrollable_);
}

/**
 * @tc.name: EdgeEffectOption004
 * @tc.desc: Test EdgeEffectOption
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestTwoNg, EdgeEffectOption004, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateListItems(1);
    CreateDone();
    EXPECT_TRUE(pattern_->GetAlwaysEnabled());
    EXPECT_TRUE(pattern_->isScrollable_);
}

/**
 * @tc.name: SetEdgeEffectCallback001
 * @tc.desc: Test SetEdgeEffectCallback
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestTwoNg, SetEdgeEffectCallback001, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetEdgeEffect(EdgeEffect::SPRING, false);
    CreateListItems(1);
    CreateDone();
    RefPtr<ScrollEdgeEffect> scrollEdgeEffect = pattern_->GetScrollEdgeEffect();
    EXPECT_EQ(scrollEdgeEffect->currentPositionCallback_(), 0);
    EXPECT_EQ(scrollEdgeEffect->leadingCallback_(), 0);
    EXPECT_EQ(scrollEdgeEffect->trailingCallback_(), 0.0);
    EXPECT_EQ(scrollEdgeEffect->initLeadingCallback_(), 0);
    EXPECT_EQ(scrollEdgeEffect->initTrailingCallback_(), 0.0);
}

/**
 * @tc.name: SetEdgeEffectCallback002
 * @tc.desc: Test SetEdgeEffectCallback
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestTwoNg, SetEdgeEffectCallback002, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetScrollSnapAlign(ScrollSnapAlign::CENTER);
    model.SetEdgeEffect(EdgeEffect::SPRING, false);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    RefPtr<ScrollEdgeEffect> scrollEdgeEffect = pattern_->GetScrollEdgeEffect();
    EXPECT_EQ(scrollEdgeEffect->currentPositionCallback_(), 150.0);
    EXPECT_EQ(scrollEdgeEffect->trailingCallback_(), 150.f);
    EXPECT_EQ(scrollEdgeEffect->initTrailingCallback_(), 150.f);
    EXPECT_TRUE(GreatNotEqual(150.0, scrollEdgeEffect->leadingCallback_()));

    ScrollToIndex(TOTAL_ITEM_NUMBER - 1, false, ScrollAlign::CENTER);
    EXPECT_EQ(scrollEdgeEffect->currentPositionCallback_(), -50.0);
    EXPECT_EQ(scrollEdgeEffect->leadingCallback_(), -50.0);
    EXPECT_EQ(scrollEdgeEffect->initLeadingCallback_(), -50.0);
    EXPECT_TRUE(LessNotEqual(-50, scrollEdgeEffect->trailingCallback_()));
}

/**
 * @tc.name: SetEdgeEffectCallback003
 * @tc.desc: Test SetEdgeEffectCallback
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestTwoNg, SetEdgeEffectCallback003, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetScrollSnapAlign(ScrollSnapAlign::CENTER);
    model.SetEdgeEffect(EdgeEffect::SPRING, false);
    CreateDone();
    RefPtr<ScrollEdgeEffect> scrollEdgeEffect = pattern_->GetScrollEdgeEffect();
    EXPECT_EQ(scrollEdgeEffect->currentPositionCallback_(), 0);
    EXPECT_EQ(scrollEdgeEffect->leadingCallback_(), 400);
    EXPECT_EQ(scrollEdgeEffect->trailingCallback_(), 0.0);
    EXPECT_EQ(scrollEdgeEffect->initLeadingCallback_(), 400);
    EXPECT_EQ(scrollEdgeEffect->initTrailingCallback_(), 0.0);
}

/**
 * @tc.name: ChainAnimation001
 * @tc.desc: Test SetChainAnimationOptions
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestTwoNg, ChainAnimation001, TestSize.Level1)
{
    constexpr float minSpace = 10.f;
    constexpr float maxSpace = 2.f;
    constexpr float conductivity = 5.f;
    constexpr float intensity = 5.f;
    ChainAnimationOptions options = {
        .minSpace = Dimension(minSpace),
        .maxSpace = Dimension(maxSpace),
        .conductivity = conductivity,
        .intensity = intensity,
        .edgeEffect = 0,
        .stiffness = DEFAULT_STIFFNESS,
        .damping = DEFAULT_DAMPING,
    };
    ListModelNG model = CreateList();
    model.SetSpace(Dimension(SPACE));
    model.SetChainAnimation(true);
    model.SetChainAnimationOptions(options);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step1. When minSpace > maxSpace.
     * @tc.expected: minSpace and maxSpace would be SPACE.
     */
    auto chainAnimation = pattern_->chainAnimation_;
    EXPECT_FLOAT_EQ(chainAnimation->minSpace_, SPACE);
    EXPECT_FLOAT_EQ(chainAnimation->maxSpace_, SPACE);

    /**
     * @tc.steps: step2. When conductivity > 1, intensity > 1.
     * @tc.expected: conductivity/intensity would be default value.
     */
    EXPECT_FLOAT_EQ(chainAnimation->conductivity_, ChainAnimation::DEFAULT_CONDUCTIVITY);
    EXPECT_FLOAT_EQ(chainAnimation->intensity_, ChainAnimation::DEFAULT_INTENSITY);

    /**
     * @tc.steps: step3. SetChainAnimationOptions again
     */
    pattern_->SetChainAnimationOptions(options);
    chainAnimation = pattern_->chainAnimation_;
    EXPECT_FLOAT_EQ(chainAnimation->minSpace_, SPACE);
    EXPECT_FLOAT_EQ(chainAnimation->maxSpace_, SPACE);
    EXPECT_FLOAT_EQ(chainAnimation->conductivity_, ChainAnimation::DEFAULT_CONDUCTIVITY);
    EXPECT_FLOAT_EQ(chainAnimation->intensity_, ChainAnimation::DEFAULT_INTENSITY);
}

/**
 * @tc.name: ChainAnimation002
 * @tc.desc: Test SetChainAnimationOptions
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestTwoNg, ChainAnimation002, TestSize.Level1)
{
    constexpr float minSpace = 2.f;
    constexpr float maxSpace = 10.f;
    constexpr float conductivity = -5.f;
    constexpr float intensity = -5.f;
    ChainAnimationOptions options = {
        .minSpace = Dimension(minSpace),
        .maxSpace = Dimension(maxSpace),
        .conductivity = conductivity,
        .intensity = intensity,
        .edgeEffect = 0,
        .stiffness = DEFAULT_STIFFNESS,
        .damping = DEFAULT_DAMPING,
    };
    ListModelNG model = CreateList();
    model.SetSpace(Dimension(SPACE));
    model.SetChainAnimation(true);
    model.SetChainAnimationOptions(options);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step1. When minSpace < maxSpace.
     * @tc.expected: minSpace and maxSpace would be itself.
     */
    auto chainAnimation = pattern_->chainAnimation_;
    EXPECT_FLOAT_EQ(chainAnimation->minSpace_, minSpace);
    EXPECT_FLOAT_EQ(chainAnimation->maxSpace_, maxSpace);

    /**
     * @tc.steps: step2. When conductivity < 0, intensity < 0
     * @tc.expected: conductivity/intensity would be default value.
     */
    EXPECT_FLOAT_EQ(chainAnimation->conductivity_, ChainAnimation::DEFAULT_CONDUCTIVITY);
    EXPECT_FLOAT_EQ(chainAnimation->intensity_, ChainAnimation::DEFAULT_INTENSITY);

    /**
     * @tc.steps: step3. SetChainAnimationOptions again
     */
    pattern_->SetChainAnimationOptions(options);
    chainAnimation = pattern_->chainAnimation_;
    EXPECT_FLOAT_EQ(chainAnimation->minSpace_, minSpace);
    EXPECT_FLOAT_EQ(chainAnimation->maxSpace_, maxSpace);
    EXPECT_FLOAT_EQ(chainAnimation->conductivity_, ChainAnimation::DEFAULT_CONDUCTIVITY);
    EXPECT_FLOAT_EQ(chainAnimation->intensity_, ChainAnimation::DEFAULT_INTENSITY);
}

/**
 * @tc.name: ChainAnimation003
 * @tc.desc: Test SetChainAnimationOptions
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestTwoNg, ChainAnimation003, TestSize.Level1)
{
    constexpr float minSpace = 2.f;
    constexpr float maxSpace = 10.f;
    constexpr float conductivity = 0;
    constexpr float intensity = 0;
    ChainAnimationOptions options = {
        .minSpace = Dimension(minSpace),
        .maxSpace = Dimension(maxSpace),
        .conductivity = conductivity,
        .intensity = intensity,
        .edgeEffect = 0,
        .stiffness = DEFAULT_STIFFNESS,
        .damping = DEFAULT_DAMPING,
    };
    ListModelNG model = CreateList();
    model.SetSpace(Dimension(SPACE));
    model.SetChainAnimation(true);
    model.SetChainAnimationOptions(options);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step1. When conductivity == 0, intensity == 0
     * @tc.expected: conductivity/intensity would be itself.
     */
    auto chainAnimation = pattern_->chainAnimation_;
    EXPECT_FLOAT_EQ(chainAnimation->conductivity_, conductivity);
    EXPECT_FLOAT_EQ(chainAnimation->intensity_, intensity);

    /**
     * @tc.steps: step2. SetChainAnimationOptions again
     */
    pattern_->SetChainAnimationOptions(options);
    chainAnimation = pattern_->chainAnimation_;
    EXPECT_FLOAT_EQ(chainAnimation->conductivity_, conductivity);
    EXPECT_FLOAT_EQ(chainAnimation->intensity_, intensity);
}

/**
 * @tc.name: GetOrCreateController001
 * @tc.desc: Test GetOrCreateController
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestTwoNg, GetOrCreateController001, TestSize.Level1)
{
    ListModelNG model;
    model.Create();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    auto controller = model.GetOrCreateController(AceType::RawPtr(frameNode));
    EXPECT_NE(controller, nullptr);
    controller = model.GetOrCreateController(AceType::RawPtr(frameNode));
    EXPECT_NE(controller, nullptr);
    CreateDone();
}

/**
 * @tc.name: ListItemCreate001
 * @tc.desc: Test ListItemModelNG Create
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestTwoNg, ListItemCreate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ListItem without or with deepRenderFunc
     * @tc.expected: Created successful
     */
    CreateList();
    ListItemModelNG itemModel;
    itemModel.Create(nullptr, V2::ListItemStyle::NONE);
    ViewStackProcessor::GetInstance()->Pop();
    itemModel.Create([](int32_t) {}, V2::ListItemStyle::NONE);
    ViewStackProcessor::GetInstance()->Pop();
    CreateDone();
    EXPECT_EQ(frameNode_->GetTotalChildCount(), 2);
}

/**
 * @tc.name: ListMaintainVisibleContentPosition001
 * @tc.desc: Test maintain visible content position
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestTwoNg, ListMaintainVisibleContentPosition001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ListItem LazyForEach
     * @tc.expected: Created successful
     */
    ListModelNG model = CreateList();
    model.SetMaintainVisibleContentPosition(true);
    CreateListItems(10);
    CreateDone();

    /**
     * @tc.steps: step1. Current start index is 2, insert Item in 0.
     * @tc.expected: Current index is 3.
     */
    ScrollToIndex(2, false, ScrollAlign::START);
    pattern_->NotifyDataChange(0, 1);
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 3);
    EXPECT_EQ(pattern_->currentOffset_, 300);

    /**
     * @tc.steps: step2. Current start index is 3, insert Item in 3.
     * @tc.expected: Current index is 4.
     */
    pattern_->NotifyDataChange(3, 1);
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 4);
    EXPECT_EQ(pattern_->currentOffset_, 400);

    /**
     * @tc.steps: step3. Current start index is 4, delete Item in 1.
     * @tc.expected: Current index is 3.
     */
    pattern_->NotifyDataChange(1, -1);
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 3);
    EXPECT_EQ(pattern_->currentOffset_, 300);

    /**
     * @tc.steps: step4. Current start index is 3, delete 3 Item in 1.
     * @tc.expected: Current index is 1.
     */
    pattern_->NotifyDataChange(1, -3);
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 1);
    EXPECT_EQ(pattern_->currentOffset_, 100);

    /**
     * @tc.steps: step5. Current start index is 1, delete 1 Item in 2.
     * @tc.expected: Current index is 1.
     */
    pattern_->NotifyDataChange(2, -1);
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 1);
    EXPECT_EQ(pattern_->currentOffset_, 100);

    /**
     * @tc.steps: step6. Current start index is 1, add Item in 2.
     * @tc.expected: Current index is 1.
     */
    pattern_->NotifyDataChange(2, 1);
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 1);
    EXPECT_EQ(pattern_->currentOffset_, 100);
}

/**
 * @tc.name: ListMaintainVisibleContentPosition002
 * @tc.desc: Test Test maintain visible content position with lanes
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestTwoNg, ListMaintainVisibleContentPosition002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ListItem LazyForEach
     * @tc.expected: Created successful
     */
    ListModelNG model = CreateList();
    model.SetMaintainVisibleContentPosition(true);
    model.SetLanes(2);
    CreateListItems(20);
    CreateDone();

    /**
     * @tc.steps: step1. Current start index is 4, insert Item in 0.
     * @tc.expected: Current start index is 4.
     */
    ScrollToIndex(4, false, ScrollAlign::START);
    pattern_->NotifyDataChange(0, 1);
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 4);
    EXPECT_EQ(pattern_->currentOffset_, 200);

    /**
     * @tc.steps: step2. Current start index is 4, insert 2 Item in 0.
     * @tc.expected: Current index is 6.
     */
    pattern_->NotifyDataChange(0, 2);
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 6);
    EXPECT_EQ(pattern_->currentOffset_, 300);

    /**
     * @tc.steps: step3. Current start index is 6, delete Item in 0.
     * @tc.expected: Current index is 4.
     */
    pattern_->NotifyDataChange(0, -1);
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 6);
    EXPECT_EQ(pattern_->currentOffset_, 300);

    /**
     * @tc.steps: step4. Current start index is 6, delete 2 Item in 0.
     * @tc.expected: Current index is 2.
     */
    pattern_->NotifyDataChange(0, -2);
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 4);
    EXPECT_EQ(pattern_->currentOffset_, 200);

    /**
     * @tc.steps: step5. Current start index is 4, delete 2 Item in 4.
     * @tc.expected: Current index is 2.
     */
    pattern_->NotifyDataChange(4, -1);
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 4);
    EXPECT_EQ(pattern_->currentOffset_, 200);

    /**
     * @tc.steps: step6. Current start index is 4, add Item in 2.
     * @tc.expected: Current index is 6.
     */
    pattern_->NotifyDataChange(4, 2);
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 6);
    EXPECT_EQ(pattern_->currentOffset_, 300);
}

/**
 * @tc.name: ListMaintainVisibleContentPosition003
 * @tc.desc: Test Test maintain visible content position with ListItemGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestTwoNg, ListMaintainVisibleContentPosition003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ListItem LazyForEach
     * @tc.expected: Created successful
     */
    ListModelNG model = CreateList();
    model.SetMaintainVisibleContentPosition(true);
    CreateListItemGroup();
    CreateListItems(10);
    CreateDone();

    /**
     * @tc.steps: step1. Current start index is 2, insert Item in 0.
     * @tc.expected: Current index is 3.
     */
    JumpToItemInGroup(0, 2, false, ScrollAlign::START);
    EXPECT_EQ(pattern_->currentOffset_, 200);
    auto groupNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    auto groupPattern = groupNode->GetPattern<ListItemGroupPattern>();
    groupPattern->NotifyDataChange(0, 1);
    FlushUITasks();
    EXPECT_EQ(groupPattern->itemDisplayStartIndex_, 3);
    EXPECT_EQ(pattern_->currentOffset_, 300);

    /**
     * @tc.steps: step2. Current start index is 3, insert Item in 3.
     * @tc.expected: Current index is 4.
     */
    groupPattern->NotifyDataChange(3, 1);
    FlushUITasks();
    EXPECT_EQ(groupPattern->itemDisplayStartIndex_, 4);
    EXPECT_EQ(pattern_->currentOffset_, 400);

    /**
     * @tc.steps: step3. Current start index is 4, delete Item in 1.
     * @tc.expected: Current index is 3.
     */
    groupPattern->NotifyDataChange(1, -1);
    FlushUITasks();
    EXPECT_EQ(groupPattern->itemDisplayStartIndex_, 3);
    EXPECT_EQ(pattern_->currentOffset_, 300);

    /**
     * @tc.steps: step4. Current start index is 3, delete 3 Item in 1.
     * @tc.expected: Current index is 1.
     */
    groupPattern->NotifyDataChange(1, -3);
    FlushUITasks();
    EXPECT_EQ(groupPattern->itemDisplayStartIndex_, 1);
    EXPECT_EQ(pattern_->currentOffset_, 100);

    /**
     * @tc.steps: step5. Current start index is 1, delete 1 Item in 2.
     * @tc.expected: Current index is 1.
     */
    groupPattern->NotifyDataChange(2, -1);
    FlushUITasks();
    EXPECT_EQ(groupPattern->itemDisplayStartIndex_, 1);
    EXPECT_EQ(pattern_->currentOffset_, 100);

    /**
     * @tc.steps: step6. Current start index is 1, add Item in 2.
     * @tc.expected: Current index is 1.
     */
    groupPattern->NotifyDataChange(2, 1);
    FlushUITasks();
    EXPECT_EQ(groupPattern->itemDisplayStartIndex_, 1);
    EXPECT_EQ(pattern_->currentOffset_, 100);
}

/**
 * @tc.name: ListMaintainVisibleContentPosition004
 * @tc.desc: Test Test maintain visible content position with ListItemGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestTwoNg, ListMaintainVisibleContentPosition004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ListItem LazyForEach
     * @tc.expected: Created successful
     */
    ListModelNG model = CreateList();
    model.SetLanes(2);
    model.SetMaintainVisibleContentPosition(true);
    CreateListItemGroup();
    CreateListItems(20);
    CreateDone();

    /**
     * @tc.steps: step1. Current start index is 2, insert Item in 0.
     * @tc.expected: Current index is 3.
     */
    JumpToItemInGroup(0, 4, false, ScrollAlign::START);
    auto groupNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    auto groupPattern = groupNode->GetPattern<ListItemGroupPattern>();
    groupPattern->NotifyDataChange(0, 1);
    FlushUITasks();
    EXPECT_EQ(groupPattern->itemDisplayStartIndex_, 4);
    EXPECT_EQ(pattern_->currentOffset_, 200);

    /**
     * @tc.steps: step2. Current start index is 4, insert 2 Item in 0.
     * @tc.expected: Current index is 6.
     */
    groupPattern->NotifyDataChange(0, 2);
    FlushUITasks();
    EXPECT_EQ(groupPattern->itemDisplayStartIndex_, 6);
    EXPECT_EQ(pattern_->currentOffset_, 300);

    /**
     * @tc.steps: step3. Current start index is 6, delete Item in 0.
     * @tc.expected: Current index is 4.
     */
    groupPattern->NotifyDataChange(0, -1);
    FlushUITasks();
    EXPECT_EQ(groupPattern->itemDisplayStartIndex_, 6);
    EXPECT_EQ(pattern_->currentOffset_, 300);

    /**
     * @tc.steps: step4. Current start index is 6, delete 2 Item in 0.
     * @tc.expected: Current index is 2.
     */
    groupPattern->NotifyDataChange(0, -2);
    FlushUITasks();
    EXPECT_EQ(groupPattern->itemDisplayStartIndex_, 4);
    EXPECT_EQ(pattern_->currentOffset_, 200);

    /**
     * @tc.steps: step5. Current start index is 4, delete 2 Item in 4.
     * @tc.expected: Current index is 2.
     */
    groupPattern->NotifyDataChange(4, -1);
    FlushUITasks();
    EXPECT_EQ(groupPattern->itemDisplayStartIndex_, 4);
    EXPECT_EQ(pattern_->currentOffset_, 200);

    /**
     * @tc.steps: step6. Current start index is 4, add Item in 4.
     * @tc.expected: Current index is 4.
     */
    groupPattern->NotifyDataChange(4, 2);
    FlushUITasks();
    EXPECT_EQ(groupPattern->itemDisplayStartIndex_, 6);
    EXPECT_EQ(pattern_->currentOffset_, 300);
}

/**
 * @tc.name: ListMaintainVisibleContentPosition005
 * @tc.desc: Test Test maintain visible content position with ListItemGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestTwoNg, ListMaintainVisibleContentPosition005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ListItem LazyForEach
     * @tc.expected: Created successful
     */
    ListModelNG model = CreateList();
    model.SetLanes(2);
    model.SetMaintainVisibleContentPosition(true);
    CreateListItemGroups(10);
    CreateDone();

    /**
     * @tc.steps: step1. Current start index is 2, insert Item in 0.
     * @tc.expected: Current index is 3.
     */
    ScrollToIndex(2, false, ScrollAlign::START);
    pattern_->NotifyDataChange(0, 1);
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 3);
    EXPECT_EQ(pattern_->currentOffset_, 300);

    /**
     * @tc.steps: step2. Current start index is 3, insert Item in 3.
     * @tc.expected: Current index is 4.
     */
    pattern_->NotifyDataChange(3, 1);
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 4);
    EXPECT_EQ(pattern_->currentOffset_, 400);

    /**
     * @tc.steps: step3. Current start index is 4, delete Item in 1.
     * @tc.expected: Current index is 3.
     */
    pattern_->NotifyDataChange(1, -1);
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 3);
    EXPECT_EQ(pattern_->currentOffset_, 300);

    /**
     * @tc.steps: step4. Current start index is 3, delete 3 Item in 1.
     * @tc.expected: Current index is 1.
     */
    pattern_->NotifyDataChange(1, -3);
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 1);
    EXPECT_EQ(pattern_->currentOffset_, 100);

    /**
     * @tc.steps: step5. Current start index is 1, delete 1 Item in 2.
     * @tc.expected: Current index is 1.
     */
    pattern_->NotifyDataChange(2, -1);
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 1);
    EXPECT_EQ(pattern_->currentOffset_, 100);

    /**
     * @tc.steps: step6. Current start index is 1, add Item in 2.
     * @tc.expected: Current index is 1.
     */
    pattern_->NotifyDataChange(2, 1);
    FlushUITasks();
    EXPECT_EQ(pattern_->startIndex_, 1);
    EXPECT_EQ(pattern_->currentOffset_, 100);
}

/**
 * @tc.name: ListMaintainVisibleContentPosition006
 * @tc.desc: Test Test maintain visible content position with ListItemGroup and space
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestTwoNg, ListMaintainVisibleContentPosition006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ListItem LazyForEach
     * @tc.expected: Created successful
     */
    ListModelNG model = CreateList();
    model.SetMaintainVisibleContentPosition(true);
    auto groupModel = CreateListItemGroup();
    groupModel.SetSpace(Dimension(10));
    CreateListItems(10);
    CreateDone();

    /**
     * @tc.steps: step1. Current start index is 0, insert 2 Item in 0.
     * @tc.expected: Current index is 2, currentOffset = 220
     */
    auto groupNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    auto groupPattern = groupNode->GetPattern<ListItemGroupPattern>();
    groupPattern->NotifyDataChange(0, 2);
    FlushUITasks();
    EXPECT_EQ(groupPattern->itemDisplayStartIndex_, 2);
    EXPECT_EQ(pattern_->currentOffset_, 220);

    /**
     * @tc.steps: step2. Current start index is 2, insert Item in 1 two times.
     * @tc.expected: Current index is 1, currentOffset = 110
     */
    groupPattern->NotifyDataChange(1, -1);
    groupPattern->NotifyDataChange(1, -1);
    FlushUITasks();
    EXPECT_EQ(groupPattern->itemDisplayStartIndex_, 1);
    EXPECT_EQ(pattern_->currentOffset_, 110);
    EXPECT_EQ(groupPattern->layoutedItemInfo_.value().startIndex, 1);

    /**
     * @tc.steps: step2. Current start index is 0, insert Item in 0 two times.
     * @tc.expected: Current index is 0, currentOffset = 0
     */
    groupPattern->NotifyDataChange(0, -1);
    groupPattern->NotifyDataChange(0, -1);
    FlushUITasks();
    EXPECT_EQ(groupPattern->itemDisplayStartIndex_, 0);
    EXPECT_EQ(pattern_->currentOffset_, 0);
    EXPECT_EQ(groupPattern->layoutedItemInfo_.value().startIndex, 0);
}

/**
 * @tc.name: ListMaintainVisibleContentPosition007
 * @tc.desc: Test Test maintain visible content position with ListItemGroup with header/footer
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestTwoNg, ListMaintainVisibleContentPosition007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ListItem LazyForEach
     * @tc.expected: Created successful
     */
    ListModelNG model = CreateList();
    model.SetMaintainVisibleContentPosition(true);
    auto groupModel = CreateListItemGroup();
    groupModel.SetSpace(Dimension(10));
    auto header = GetRowOrColBuilder(FILL_LENGTH, Dimension(GROUP_HEADER_LEN));
    groupModel.SetHeader(std::move(header));
    auto footer = GetRowOrColBuilder(FILL_LENGTH, Dimension(GROUP_HEADER_LEN));
    groupModel.SetFooter(std::move(footer));
    CreateListItems(10);
    CreateDone();

    /**
     * @tc.steps: step1. Current start index is 0, insert 1 Item in 0.
     * @tc.expected: Current index is 0, currentOffset = 0
     */
    auto groupNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    auto groupPattern = groupNode->GetPattern<ListItemGroupPattern>();
    groupPattern->NotifyDataChange(1, 1);
    FlushUITasks();
    EXPECT_EQ(groupPattern->itemDisplayStartIndex_, 0);
    EXPECT_EQ(pattern_->currentOffset_, 0);

    /**
     * @tc.steps: step2. Scroll to listItem1, insert 1 Item in 0.
     * @tc.expected: Current index is 2, currentOffset = 260
     */
    UpdateCurrentOffset(-160);
    EXPECT_EQ(pattern_->currentOffset_, 160);
    groupPattern->NotifyDataChange(1, 1);
    FlushUITasks();
    EXPECT_EQ(groupPattern->itemDisplayStartIndex_, 2);
    EXPECT_EQ(pattern_->currentOffset_, 260);

    /**
     * @tc.steps: step3. Scroll to listItem1, delete 1 Item in 0.
     * @tc.expected: Current index is 1, currentOffset = 260
     */
    groupPattern->NotifyDataChange(1, -1);
    FlushUITasks();
    EXPECT_EQ(groupPattern->itemDisplayStartIndex_, 1);
    EXPECT_EQ(pattern_->currentOffset_, 160);
}

/**
 * @tc.name: ListMaintainVisibleContentPosition008
 * @tc.desc: Test Test maintain visible content position with ListItemGroup with header/footer, delete all item in Group
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestTwoNg, ListMaintainVisibleContentPosition008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ListItem LazyForEach
     * @tc.expected: Created successful
     */
    ListModelNG model = CreateList();
    model.SetMaintainVisibleContentPosition(true);
    for (int32_t i = 0; i < 4; i++) {
        auto groupModel = CreateListItemGroup();
        auto header = GetRowOrColBuilder(FILL_LENGTH, Dimension(GROUP_HEADER_LEN));
        groupModel.SetHeader(std::move(header));
        auto footer = GetRowOrColBuilder(FILL_LENGTH, Dimension(GROUP_HEADER_LEN));
        groupModel.SetFooter(std::move(footer));
        CreateListItems(1);
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    CreateDone();

    /**
     * @tc.steps: step1. Scroll To first Group footer.
     * @tc.expected: Current offset is 175
     */
    UpdateCurrentOffset(-175);
    EXPECT_EQ(pattern_->currentOffset_, 175);

    /**
     * @tc.steps: step2. Current start index is 0, insert 1 Item in 0.
     * @tc.expected: Current index is 0, currentOffset = 0
     */
    auto groupNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    auto groupPattern = groupNode->GetPattern<ListItemGroupPattern>();
    groupPattern->NotifyDataChange(1, -1);
    groupNode->RemoveChildAtIndex(1);
    FlushUITasks();
    EXPECT_EQ(pattern_->currentOffset_, 75);
}

/**
 * @tc.name: SetScrollSnapAnimationSpeed001
 * @tc.desc: Test SetScrollSnapAnimationSpeed.
 * @tc.type: FUNC
 */
HWTEST_F(ListAttrTestTwoNg, SetScrollSnapAnimationSpeed001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List.
     * @tc.expected: Created successful.
     */
    ListModelNG model = CreateList();
    EXPECT_EQ(model.GetScrollSnapAnimationSpeed(AceType::RawPtr(frameNode_)), ScrollSnapAnimationSpeed::NORMAL);
    pattern_->scrollable_ = AceType::MakeRefPtr<Scrollable>();
    /**
     * @tc.steps: step2. Set speed slow.
     * @tc.expected: Current scroll snap animation speed is slow.
     */
    model.SetScrollSnapAnimationSpeed(ScrollSnapAnimationSpeed::SLOW);
    EXPECT_EQ(model.GetScrollSnapAnimationSpeed(AceType::RawPtr(frameNode_)), ScrollSnapAnimationSpeed::SLOW);

    /**
     * @tc.steps: step3. Set speed normal.
     * @tc.expected: Current scroll snap animation speed is normal.
     */
    model.SetScrollSnapAnimationSpeed(AceType::RawPtr(frameNode_), ScrollSnapAnimationSpeed::NORMAL);
    EXPECT_EQ(model.GetScrollSnapAnimationSpeed(AceType::RawPtr(frameNode_)), ScrollSnapAnimationSpeed::NORMAL);
}
} // namespace OHOS::Ace::NG
