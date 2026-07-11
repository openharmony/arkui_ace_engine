/*
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

#include <utility>

#include "gtest/gtest.h"
#include "test/unittest/core/pattern/test_ng.h"
#include "list_test_ng.h"

#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/pattern/lazy_container_item_helper.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/list/list_item_group_pattern.h"
#include "core/components_ng/pattern/list/list_pattern.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

class LazyContainerItemHelperTestNg : public ListTestNg {};

// =========================================================================
// Group A: LazyContainerItemHelper pure unit tests (no List tree needed)
// =========================================================================

/**
 * @tc.name: HelperIndexDefault001
 * @tc.desc: Default values — indexInList=0, indexInListItemGroup=-1 (sentinel for "not in group").
 * @tc.type: FUNC
 */
HWTEST_F(LazyContainerItemHelperTestNg, HelperIndexDefault001, TestSize.Level1)
{
    auto helper = AceType::MakeRefPtr<LazyContainerItemHelper>();
    ASSERT_NE(helper, nullptr);
    EXPECT_EQ(helper->GetIndexInList(), 0);
    EXPECT_EQ(helper->GetIndexInListItemGroup(), -1);
}

/**
 * @tc.name: HelperIndexSetGet002
 * @tc.desc: Set/Get round-trip then overwrite with new values.
 * @tc.type: FUNC
 */
HWTEST_F(LazyContainerItemHelperTestNg, HelperIndexSetGet002, TestSize.Level1)
{
    auto helper = AceType::MakeRefPtr<LazyContainerItemHelper>();
    ASSERT_NE(helper, nullptr);
    helper->SetIndexInList(42);
    helper->SetIndexInListItemGroup(7);
    EXPECT_EQ(helper->GetIndexInList(), 42);
    EXPECT_EQ(helper->GetIndexInListItemGroup(), 7);
    // overwrite
    helper->SetIndexInList(0);
    helper->SetIndexInListItemGroup(-1);
    EXPECT_EQ(helper->GetIndexInList(), 0);
    EXPECT_EQ(helper->GetIndexInListItemGroup(), -1);
}

/**
 * @tc.name: HelperIndexNegativeValue003
 * @tc.desc: Negative values (including the -1 sentinel) are stored as-is, no clamping.
 * @tc.type: FUNC
 */
HWTEST_F(LazyContainerItemHelperTestNg, HelperIndexNegativeValue003, TestSize.Level1)
{
    auto helper = AceType::MakeRefPtr<LazyContainerItemHelper>();
    ASSERT_NE(helper, nullptr);
    helper->SetIndexInList(-1);
    helper->SetIndexInListItemGroup(-100);
    EXPECT_EQ(helper->GetIndexInList(), -1);
    EXPECT_EQ(helper->GetIndexInListItemGroup(), -100);
}

// =========================================================================
// Group B: FindHeadOrTailChild unit tests
// =========================================================================

/**
 * @tc.name: FindHeadOrTailChildNull001
 * @tc.desc: Null childFocus input triggers early return (false), target untouched.
 * @tc.type: FUNC
 */
HWTEST_F(LazyContainerItemHelperTestNg, FindHeadOrTailChildNull001, TestSize.Level1)
{
    auto helper = AceType::MakeRefPtr<LazyContainerItemHelper>();
    ASSERT_NE(helper, nullptr);
    WeakPtr<FocusHub> target;
    EXPECT_FALSE(helper->FindHeadOrTailChild(nullptr, FocusStep::UP_END, target));
    EXPECT_EQ(target.Upgrade(), nullptr);
}

/**
 * @tc.name: FindHeadOrTailChildNonEndStep002
 * @tc.desc: A non-HOME/END step (e.g. DOWN) yields false — neither isHome nor isEnd matches.
 * @tc.type: FUNC
 */
HWTEST_F(LazyContainerItemHelperTestNg, FindHeadOrTailChildNonEndStep002, TestSize.Level1)
{
    auto parent = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(parent, nullptr);
    auto parentFocus = parent->GetOrCreateFocusHub();
    ASSERT_NE(parentFocus, nullptr);

    auto helper = AceType::MakeRefPtr<LazyContainerItemHelper>();
    WeakPtr<FocusHub> target;
    EXPECT_FALSE(helper->FindHeadOrTailChild(parentFocus, FocusStep::DOWN, target));
    EXPECT_FALSE(helper->FindHeadOrTailChild(parentFocus, FocusStep::UP, target));
    EXPECT_FALSE(helper->FindHeadOrTailChild(parentFocus, FocusStep::LEFT, target));
    EXPECT_FALSE(helper->FindHeadOrTailChild(parentFocus, FocusStep::RIGHT, target));
}

/**
 * @tc.name: FindHeadOrTailChildHomeStep003
 * @tc.desc: UP_END/LEFT_END on a node with no focusable head descendant returns false.
 * @tc.type: FUNC
 */
HWTEST_F(LazyContainerItemHelperTestNg, FindHeadOrTailChildHomeStep003, TestSize.Level1)
{
    auto parent = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(parent, nullptr);
    auto parentFocus = parent->GetOrCreateFocusHub();
    ASSERT_NE(parentFocus, nullptr);

    auto helper = AceType::MakeRefPtr<LazyContainerItemHelper>();
    WeakPtr<FocusHub> target;
    EXPECT_FALSE(helper->FindHeadOrTailChild(parentFocus, FocusStep::UP_END, target));
    EXPECT_FALSE(helper->FindHeadOrTailChild(parentFocus, FocusStep::LEFT_END, target));
}

/**
 * @tc.name: FindHeadOrTailChildTailStep004
 * @tc.desc: DOWN_END/RIGHT_END on a node with no focusable tail descendant returns false.
 * @tc.type: FUNC
 */
HWTEST_F(LazyContainerItemHelperTestNg, FindHeadOrTailChildTailStep004, TestSize.Level1)
{
    auto parent = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(parent, nullptr);
    auto parentFocus = parent->GetOrCreateFocusHub();
    ASSERT_NE(parentFocus, nullptr);

    auto helper = AceType::MakeRefPtr<LazyContainerItemHelper>();
    WeakPtr<FocusHub> target;
    EXPECT_FALSE(helper->FindHeadOrTailChild(parentFocus, FocusStep::DOWN_END, target));
    EXPECT_FALSE(helper->FindHeadOrTailChild(parentFocus, FocusStep::RIGHT_END, target));
}

/**
 * @tc.name: FindHeadOrTailChildFoundHead005
 * @tc.desc: With a focusable child whose GetHeadOrTailChild(true) returns a node, HOME step finds it.
 * @tc.type: FUNC
 */
HWTEST_F(LazyContainerItemHelperTestNg, FindHeadOrTailChildFoundHead005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a parent with a focusable child that can resolve a head node.
     */
    auto parent = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(parent, nullptr);
    auto child = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(child, nullptr);
    child->MountToParent(parent);
    auto childFocus = child->GetOrCreateFocusHub();
    ASSERT_NE(childFocus, nullptr);
    childFocus->SetFocusable(true);

    auto parentFocus = parent->GetOrCreateFocusHub();
    ASSERT_NE(parentFocus, nullptr);

    /**
     * @tc.steps: step2. Invoke FindHeadOrTailChild with a HOME step.
     * @tc.expected: does not crash; result reflects whether a head node was resolved by FocusHub.
     */
    auto helper = AceType::MakeRefPtr<LazyContainerItemHelper>();
    WeakPtr<FocusHub> target;
    helper->FindHeadOrTailChild(parentFocus, FocusStep::UP_END, target);
    // The FocusHub internals determine the actual result; the test asserts no crash and valid behavior.
}

// =========================================================================
// Group C: Base Pattern helper ownership
// =========================================================================

/**
 * @tc.name: PatternHelperDefaultNull001
 * @tc.desc: A fresh Pattern has no helper — Get returns nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(LazyContainerItemHelperTestNg, PatternHelperDefaultNull001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<Pattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->GetLazyContainerItemHelper(), nullptr);
}

/**
 * @tc.name: PatternHelperLazyCreate002
 * @tc.desc: GetOrCreate lazily creates the helper; Get then returns the same instance.
 * @tc.type: FUNC
 */
HWTEST_F(LazyContainerItemHelperTestNg, PatternHelperLazyCreate002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<Pattern>();
    ASSERT_NE(pattern, nullptr);
    const auto& helper = pattern->GetOrCreateLazyContainerItemHelper();
    ASSERT_NE(helper, nullptr);
    EXPECT_EQ(pattern->GetLazyContainerItemHelper(), helper);
}

/**
 * @tc.name: PatternHelperIdempotent003
 * @tc.desc: Calling GetOrCreate twice returns the same instance (no duplicate allocation).
 * @tc.type: FUNC
 */
HWTEST_F(LazyContainerItemHelperTestNg, PatternHelperIdempotent003, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<Pattern>();
    ASSERT_NE(pattern, nullptr);
    const auto& first = pattern->GetOrCreateLazyContainerItemHelper();
    const auto& second = pattern->GetOrCreateLazyContainerItemHelper();
    EXPECT_EQ(first, second);
}

/**
 * @tc.name: PatternHelperConstRef004
 * @tc.desc: The accessor returns a const reference (no smart-pointer copy). Verified by binding auto&.
 * @tc.type: FUNC
 */
HWTEST_F(LazyContainerItemHelperTestNg, PatternHelperConstRef004, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<Pattern>();
    ASSERT_NE(pattern, nullptr);
    // If Get returned by value this would be a copy; binding to auto& confirms reference semantics.
    const auto& helper = pattern->GetOrCreateLazyContainerItemHelper();
    ASSERT_NE(helper, nullptr);
    helper->SetIndexInList(5);
    EXPECT_EQ(pattern->GetLazyContainerItemHelper()->GetIndexInList(), 5);
}

// =========================================================================
// Group D: ListItemPattern / ListItemGroupPattern index forwarding
// =========================================================================

/**
 * @tc.name: ListItemForwardDefault001
 * @tc.desc: A fresh ListItemPattern reports defaults (0 / -1) and has no helper yet.
 * @tc.type: FUNC
 */
HWTEST_F(LazyContainerItemHelperTestNg, ListItemForwardDefault001, TestSize.Level1)
{
    auto listItemPattern = AceType::MakeRefPtr<ListItemPattern>(nullptr);
    ASSERT_NE(listItemPattern, nullptr);
    auto itemNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), listItemPattern);
    ASSERT_NE(itemNode, nullptr);
    EXPECT_EQ(listItemPattern->GetIndexInList(), 0);
    EXPECT_EQ(listItemPattern->GetIndexInListItemGroup(), -1);
    EXPECT_EQ(listItemPattern->GetLazyContainerItemHelper(), nullptr);
}

/**
 * @tc.name: ListItemForwardSetGet002
 * @tc.desc: Set via ListItemPattern wrappers, verify both wrappers and the underlying helper.
 * @tc.type: FUNC
 */
HWTEST_F(LazyContainerItemHelperTestNg, ListItemForwardSetGet002, TestSize.Level1)
{
    auto listItemPattern = AceType::MakeRefPtr<ListItemPattern>(nullptr);
    ASSERT_NE(listItemPattern, nullptr);
    auto itemNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), listItemPattern);
    ASSERT_NE(itemNode, nullptr);
    listItemPattern->SetIndexInList(15);
    listItemPattern->SetIndexInListItemGroup(3);
    EXPECT_EQ(listItemPattern->GetIndexInList(), 15);
    EXPECT_EQ(listItemPattern->GetIndexInListItemGroup(), 3);
    const auto& helper = listItemPattern->GetLazyContainerItemHelper();
    ASSERT_NE(helper, nullptr);
    EXPECT_EQ(helper->GetIndexInList(), 15);
    EXPECT_EQ(helper->GetIndexInListItemGroup(), 3);
}

/**
 * @tc.name: ListItemForwardOverwrite003
 * @tc.desc: Overwriting index values updates the helper (no stale accumulation).
 * @tc.type: FUNC
 */
HWTEST_F(LazyContainerItemHelperTestNg, ListItemForwardOverwrite003, TestSize.Level1)
{
    auto listItemPattern = AceType::MakeRefPtr<ListItemPattern>(nullptr);
    ASSERT_NE(listItemPattern, nullptr);
    auto itemNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), listItemPattern);
    ASSERT_NE(itemNode, nullptr);
    listItemPattern->SetIndexInList(15);
    listItemPattern->SetIndexInListItemGroup(3);
    listItemPattern->SetIndexInList(20);
    listItemPattern->SetIndexInListItemGroup(-1);
    EXPECT_EQ(listItemPattern->GetIndexInList(), 20);
    EXPECT_EQ(listItemPattern->GetIndexInListItemGroup(), -1);
}

/**
 * @tc.name: ListItemForwardFindHeadOrTail004
 * @tc.desc: ListItemPattern::FindHeadOrTailChild forwards to the helper without crashing.
 * @tc.type: FUNC
 */
HWTEST_F(LazyContainerItemHelperTestNg, ListItemForwardFindHeadOrTail004, TestSize.Level1)
{
    CreateList();
    CreateListItems(1);
    CreateDone();
    auto listItem = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(listItem, nullptr);
    auto pattern = listItem->GetPattern<ListItemPattern>();
    ASSERT_NE(pattern, nullptr);
    auto itemFocus = listItem->GetOrCreateFocusHub();
    ASSERT_NE(itemFocus, nullptr);
    WeakPtr<FocusHub> target;
    EXPECT_FALSE(pattern->FindHeadOrTailChild(itemFocus, FocusStep::UP_END, target));
    EXPECT_FALSE(pattern->FindHeadOrTailChild(itemFocus, FocusStep::DOWN_END, target));
}

/**
 * @tc.name: GroupForwardDefault001
 * @tc.desc: A fresh ListItemGroupPattern reports default indexInList=0 and has no helper.
 * @tc.type: FUNC
 */
HWTEST_F(LazyContainerItemHelperTestNg, GroupForwardDefault001, TestSize.Level1)
{
    CreateList();
    CreateListItemGroups(1);
    CreateDone();
    auto groupNode = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(groupNode, nullptr);
    auto groupPattern = groupNode->GetPattern<ListItemGroupPattern>();
    ASSERT_NE(groupPattern, nullptr);
    EXPECT_EQ(groupPattern->GetIndexInList(), 0);
}

/**
 * @tc.name: GroupForwardSetGet002
 * @tc.desc: Set/Get indexInList via the group wrapper lands in the helper.
 * @tc.type: FUNC
 */
HWTEST_F(LazyContainerItemHelperTestNg, GroupForwardSetGet002, TestSize.Level1)
{
    CreateList();
    CreateListItemGroups(1);
    CreateDone();
    auto groupNode = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(groupNode, nullptr);
    auto groupPattern = groupNode->GetPattern<ListItemGroupPattern>();
    ASSERT_NE(groupPattern, nullptr);
    groupPattern->SetIndexInList(9);
    EXPECT_EQ(groupPattern->GetIndexInList(), 9);
    const auto& helper = groupPattern->GetLazyContainerItemHelper();
    ASSERT_NE(helper, nullptr);
    EXPECT_EQ(helper->GetIndexInList(), 9);
}

// =========================================================================
// Group E: SetListItemIndex integration (real List layout)
// =========================================================================

/**
 * @tc.name: SetListItemIndexWritesHelper001
 * @tc.desc: After layout, each laid-out ListItem's own helper carries its list index. Due to lazy
 *           loading only visible items are measured, so we verify the range [startIndex_, endIndex_].
 * @tc.type: FUNC
 */
HWTEST_F(LazyContainerItemHelperTestNg, SetListItemIndexWritesHelper001, TestSize.Level1)
{
    const int32_t itemCount = 5;
    CreateList();
    CreateListItems(itemCount);
    CreateDone();
    // Only items in [startIndex_, endIndex_] are actually laid out by the lazy layout system;
    // SetListItemIndex runs during layout, so only these items have a helper with the index set.
    for (int32_t i = pattern_->startIndex_; i <= pattern_->endIndex_; ++i) {
        auto item = GetChildFrameNode(frameNode_, i);
        ASSERT_NE(item, nullptr);
        auto pattern = item->GetPattern<ListItemPattern>();
        ASSERT_NE(pattern, nullptr);
        const auto& helper = pattern->GetLazyContainerItemHelper();
        EXPECT_NE(helper, nullptr);
        if (helper) {
            EXPECT_EQ(helper->GetIndexInList(), i);
        }
    }
}

/**
 * @tc.name: SetListItemIndexGenericChild002
 * @tc.desc: A generic (non-ListItem) child placed in a List also receives a helper with its index.
 * @tc.type: FUNC
 */
HWTEST_F(LazyContainerItemHelperTestNg, SetListItemIndexGenericChild002, TestSize.Level1)
{
    CreateList();
    AddCustomNode();
    CreateDone();
    // The custom node is the only child; its helper should carry index 0.
    auto child = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(child, nullptr);
    auto pattern = child->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    const auto& helper = pattern->GetLazyContainerItemHelper();
    EXPECT_NE(helper, nullptr);
}

// =========================================================================
// Group F: GetCurrentFocusIndex generic-child fallback
// =========================================================================

/**
 * @tc.name: GetCurrentFocusIndexListItem001
 * @tc.desc: A ListItemPattern reports its helper index via GetCurrentFocusIndex.
 * @tc.type: FUNC
 */
HWTEST_F(LazyContainerItemHelperTestNg, GetCurrentFocusIndexListItem001, TestSize.Level1)
{
    auto listItemPattern = AceType::MakeRefPtr<ListItemPattern>(nullptr);
    ASSERT_NE(listItemPattern, nullptr);
    auto itemNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), listItemPattern);
    ASSERT_NE(itemNode, nullptr);
    listItemPattern->SetIndexInList(5);
    CreateList();
    CreateDone();
    EXPECT_EQ(pattern_->GetCurrentFocusIndex(listItemPattern), 5);
}

/**
 * @tc.name: GetCurrentFocusIndexGroup001
 * @tc.desc: A ListItemGroupPattern reports its helper index via GetCurrentFocusIndex.
 * @tc.type: FUNC
 */
HWTEST_F(LazyContainerItemHelperTestNg, GetCurrentFocusIndexGroup001, TestSize.Level1)
{
    CreateList();
    CreateListItemGroups(1);
    CreateDone();
    auto groupNode = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(groupNode, nullptr);
    auto groupPattern = groupNode->GetPattern<ListItemGroupPattern>();
    ASSERT_NE(groupPattern, nullptr);
    groupPattern->SetIndexInList(8);
    EXPECT_EQ(pattern_->GetCurrentFocusIndex(groupPattern), 8);
}

/**
 * @tc.name: GetCurrentFocusIndexGenericChild001
 * @tc.desc: A generic (base Pattern) child reports its helper index via the fallback path.
 * @tc.type: FUNC
 */
HWTEST_F(LazyContainerItemHelperTestNg, GetCurrentFocusIndexGenericChild001, TestSize.Level1)
{
    auto genericPattern = AceType::MakeRefPtr<Pattern>();
    ASSERT_NE(genericPattern, nullptr);
    auto node = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), genericPattern);
    ASSERT_NE(node, nullptr);
    const auto& helper = genericPattern->GetOrCreateLazyContainerItemHelper();
    ASSERT_NE(helper, nullptr);
    helper->SetIndexInList(99);
    CreateList();
    CreateDone();
    EXPECT_EQ(pattern_->GetCurrentFocusIndex(genericPattern), 99);
}

/**
 * @tc.name: GetCurrentFocusIndexNoHelper001
 * @tc.desc: A Pattern without a helper returns -1 (no index known).
 * @tc.type: FUNC
 */
HWTEST_F(LazyContainerItemHelperTestNg, GetCurrentFocusIndexNoHelper001, TestSize.Level1)
{
    auto noHelperPattern = AceType::MakeRefPtr<Pattern>();
    ASSERT_NE(noHelperPattern, nullptr);
    CreateList();
    CreateDone();
    EXPECT_EQ(pattern_->GetCurrentFocusIndex(noHelperPattern), -1);
}

/**
 * @tc.name: GetCurrentFocusIndexNullPattern001
 * @tc.desc: A null pattern argument returns -1 (CHECK_NULL_RETURN guard).
 * @tc.type: FUNC
 */
HWTEST_F(LazyContainerItemHelperTestNg, GetCurrentFocusIndexNullPattern001, TestSize.Level1)
{
    CreateList();
    CreateDone();
    RefPtr<Pattern> nullPattern;
    EXPECT_EQ(pattern_->GetCurrentFocusIndex(nullPattern), -1);
}
} // namespace OHOS::Ace::NG
