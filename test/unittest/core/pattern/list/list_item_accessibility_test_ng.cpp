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

#include "gtest/gtest.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/list/list_item_accessibility_property.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

class ListItemAccessibilityTestNg : public TestNG {};

/**
 * @tc.name: SetSpecificSupportAction001
 * @tc.desc: Test ListItemAccessibilityProperty SetSpecificSupportAction
 * @tc.type: FUNC
 */
HWTEST_F(ListItemAccessibilityTestNg, SetSpecificSupportAction001, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, listItemPattern);
    WeakPtr<FrameNode> node = frameNode;
    RefPtr<ListItemAccessibilityProperty> listItemAccessibilityProperty =
        AceType::MakeRefPtr<ListItemAccessibilityProperty>();
    listItemAccessibilityProperty->host_ = node;
    listItemPattern->swiperIndex_ = ListItemSwipeIndex::SWIPER_START;
    listItemPattern->swipeActionState_ = SwipeActionState::EXPANDED;
    listItemPattern->startNodeIndex_ = 2;
    listItemAccessibilityProperty->SetSpecificSupportAction();
    uint64_t expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SELECT);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_CLEAR_SELECTION);
    EXPECT_EQ(listItemAccessibilityProperty->supportActions_, expectActions);
}

/**
 * @tc.name: SetSpecificSupportAction002
 * @tc.desc: Test ListItemAccessibilityProperty SetSpecificSupportAction
 * @tc.type: FUNC
 */
HWTEST_F(ListItemAccessibilityTestNg, SetSpecificSupportAction002, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, listItemPattern);
    WeakPtr<FrameNode> node = frameNode;
    RefPtr<ListItemAccessibilityProperty> listItemAccessibilityProperty =
        AceType::MakeRefPtr<ListItemAccessibilityProperty>();
    listItemAccessibilityProperty->host_ = node;
    listItemPattern->swiperIndex_ = ListItemSwipeIndex::SWIPER_START;
    listItemPattern->swipeActionState_ = SwipeActionState::COLLAPSED;
    listItemPattern->startNodeIndex_ = 2;
    listItemAccessibilityProperty->SetSpecificSupportAction();
    uint64_t expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SELECT);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_CLEAR_SELECTION);
    EXPECT_EQ(listItemAccessibilityProperty->supportActions_, expectActions);
}

/**
 * @tc.name: SetSpecificSupportAction003
 * @tc.desc: Test ListItemAccessibilityProperty SetSpecificSupportAction
 * @tc.type: FUNC
 */
HWTEST_F(ListItemAccessibilityTestNg, SetSpecificSupportAction003, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, listItemPattern);
    WeakPtr<FrameNode> node = frameNode;
    RefPtr<ListItemAccessibilityProperty> listItemAccessibilityProperty =
        AceType::MakeRefPtr<ListItemAccessibilityProperty>();
    listItemAccessibilityProperty->host_ = node;
    listItemPattern->swiperIndex_ = ListItemSwipeIndex::SWIPER_ACTION;
    listItemPattern->swipeActionState_ = SwipeActionState::EXPANDED;
    listItemPattern->startNodeIndex_ = 2;
    listItemAccessibilityProperty->SetSpecificSupportAction();
    uint64_t expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SELECT);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_CLEAR_SELECTION);
    EXPECT_EQ(listItemAccessibilityProperty->supportActions_, expectActions);
}

/**
 * @tc.name: SetSpecificSupportAction004
 * @tc.desc: Test ListItemAccessibilityProperty SetSpecificSupportAction
 * @tc.type: FUNC
 */
HWTEST_F(ListItemAccessibilityTestNg, SetSpecificSupportAction004, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, listItemPattern);
    WeakPtr<FrameNode> node = frameNode;
    RefPtr<ListItemAccessibilityProperty> listItemAccessibilityProperty =
        AceType::MakeRefPtr<ListItemAccessibilityProperty>();
    listItemAccessibilityProperty->host_ = node;
    listItemPattern->swiperIndex_ = ListItemSwipeIndex::SWIPER_ACTION;
    listItemPattern->swipeActionState_ = SwipeActionState::COLLAPSED;
    listItemPattern->startNodeIndex_ = 2;
    listItemAccessibilityProperty->SetSpecificSupportAction();
    uint64_t expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SELECT);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_CLEAR_SELECTION);
    EXPECT_EQ(listItemAccessibilityProperty->supportActions_, expectActions);
}

/**
 * @tc.name: SetSpecificSupportAction005
 * @tc.desc: Test ListItemAccessibilityProperty SetSpecificSupportAction
 * @tc.type: FUNC
 */
HWTEST_F(ListItemAccessibilityTestNg, SetSpecificSupportAction005, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, listItemPattern);
    WeakPtr<FrameNode> node = frameNode;
    RefPtr<ListItemAccessibilityProperty> listItemAccessibilityProperty =
        AceType::MakeRefPtr<ListItemAccessibilityProperty>();
    listItemAccessibilityProperty->host_ = node;
    listItemPattern->swiperIndex_ = ListItemSwipeIndex::SWIPER_END;
    listItemPattern->swipeActionState_ = SwipeActionState::EXPANDED;
    listItemPattern->endNodeIndex_ = 2;
    listItemAccessibilityProperty->SetSpecificSupportAction();
    uint64_t expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SELECT);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_CLEAR_SELECTION);
    EXPECT_EQ(listItemAccessibilityProperty->supportActions_, expectActions);
}

/**
 * @tc.name: SetSpecificSupportAction006
 * @tc.desc: Test ListItemAccessibilityProperty SetSpecificSupportAction
 * @tc.type: FUNC
 */
HWTEST_F(ListItemAccessibilityTestNg, SetSpecificSupportAction006, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, listItemPattern);
    WeakPtr<FrameNode> node = frameNode;
    RefPtr<ListItemAccessibilityProperty> listItemAccessibilityProperty =
        AceType::MakeRefPtr<ListItemAccessibilityProperty>();
    listItemAccessibilityProperty->host_ = node;
    listItemPattern->swiperIndex_ = ListItemSwipeIndex::SWIPER_END;
    listItemPattern->swipeActionState_ = SwipeActionState::COLLAPSED;
    listItemPattern->endNodeIndex_ = 2;
    listItemAccessibilityProperty->SetSpecificSupportAction();
    uint64_t expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SELECT);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_CLEAR_SELECTION);
    EXPECT_EQ(listItemAccessibilityProperty->supportActions_, expectActions);
}

/**
 * @tc.name: SetSpecificSupportAction007
 * @tc.desc: Test ListItemAccessibilityProperty SetSpecificSupportAction
 * @tc.type: FUNC
 */
HWTEST_F(ListItemAccessibilityTestNg, SetSpecificSupportAction007, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, listItemPattern);
    WeakPtr<FrameNode> node = frameNode;
    RefPtr<ListItemAccessibilityProperty> listItemAccessibilityProperty =
        AceType::MakeRefPtr<ListItemAccessibilityProperty>();
    listItemAccessibilityProperty->host_ = node;
    listItemPattern->swiperIndex_ = ListItemSwipeIndex::SWIPER_ACTION;
    listItemPattern->swipeActionState_ = SwipeActionState::EXPANDED;
    listItemPattern->endNodeIndex_ = 2;
    listItemAccessibilityProperty->SetSpecificSupportAction();
    uint64_t expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SELECT);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_CLEAR_SELECTION);
    EXPECT_EQ(listItemAccessibilityProperty->supportActions_, expectActions);
}

/**
 * @tc.name: SetSpecificSupportAction008
 * @tc.desc: Test ListItemAccessibilityProperty SetSpecificSupportAction
 * @tc.type: FUNC
 */
HWTEST_F(ListItemAccessibilityTestNg, SetSpecificSupportAction008, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, listItemPattern);
    WeakPtr<FrameNode> node = frameNode;
    RefPtr<ListItemAccessibilityProperty> listItemAccessibilityProperty =
        AceType::MakeRefPtr<ListItemAccessibilityProperty>();
    listItemAccessibilityProperty->host_ = node;
    listItemPattern->swiperIndex_ = ListItemSwipeIndex::SWIPER_ACTION;
    listItemPattern->swipeActionState_ = SwipeActionState::COLLAPSED;
    listItemPattern->endNodeIndex_ = 2;
    listItemAccessibilityProperty->SetSpecificSupportAction();
    uint64_t expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SELECT);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_CLEAR_SELECTION);
    EXPECT_EQ(listItemAccessibilityProperty->supportActions_, expectActions);
}
} // namespace OHOS::Ace::NG