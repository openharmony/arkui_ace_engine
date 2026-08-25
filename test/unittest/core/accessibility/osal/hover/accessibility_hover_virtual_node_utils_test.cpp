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

#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "adapter/ohos/osal/accessibility/hover/accessibility_hover_virtual_node_utils.h"
#include "base/log/dump_log.h"
#include "frameworks/core/accessibility/utils/accessibility_manager_utils.h"
#include "frameworks/core/components_ng/property/accessibility_property.h"

using namespace OHOS::Ace::NG;
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_NODE_ID_ROOT = 1;
constexpr int32_t TEST_NODE_ID_CHILD = 2;
constexpr int32_t TEST_NODE_ID_GRANDCHILD = 3;
constexpr int32_t TEST_NODE_ID_GRANDGRANDCHILD = 4;
constexpr int32_t TEST_NODE_ID_UNRELATED = 100;
constexpr int32_t DEPTH = 64;
constexpr char TEXT[] = "hello text";
constexpr char ROLE[] = "button";
constexpr uint64_t ACTIONS = 0x123456789ABCDEF0;
} // namespace

class AccessibilityHoverVirtualNodeUtilsTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
        MockContainer::SetUp();
        MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
        MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
        MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;

        std::unique_ptr<std::ostream> ostream = std::make_unique<std::ostringstream>();
        ASSERT_NE(ostream, nullptr);
        DumpLog::GetInstance().SetDumpFile(std::move(ostream));
    }

    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
        MockContainer::TearDown();
    }

    void SetUp() override
    {
        VirtualNodeContainerIdManager::GetInstance().Clear();
    }

    void TearDown() override
    {
        VirtualNodeContainerIdManager::GetInstance().Clear();
    }
};

// ==================== AddChild: basic scenarios ====================

/**
 * @tc.name: AddChildNullptr001
 * @tc.desc: Test AddChild with nullptr child is a no-op
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHoverVirtualNodeUtilsTest, AddChildNullptr001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create parent node and call AddChild with nullptr
     * @tc.expected: parent has no children and no crash
     */
    auto parent = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(parent, nullptr);
    parent->AddChild(nullptr);
    EXPECT_FALSE(parent->HasChildren());
    EXPECT_EQ(parent->GetChildCount(), 0u);
}

/**
 * @tc.name: AddChildNormal001
 * @tc.desc: Test AddChild with valid child sets parent and adds to children list
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHoverVirtualNodeUtilsTest, AddChildNormal001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create parent and child, call AddChild
     * @tc.expected: child's parent is parent; parent's children contains child
     */
    auto parent = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    auto child = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(parent, nullptr);
    ASSERT_NE(child, nullptr);
    parent->AddChild(child);
    EXPECT_EQ(child->GetParent(), parent);
    EXPECT_EQ(parent->GetChildCount(), 1u);
    EXPECT_EQ(parent->GetChild(0), child);
}

/**
 * @tc.name: AddChildNormal002
 * @tc.desc: Test AddChild appends multiple children preserving order
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHoverVirtualNodeUtilsTest, AddChildNormal002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. add multiple children sequentially
     * @tc.expected: children appear in insertion order
     */
    auto parent = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    auto child1 = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    auto child2 = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(parent, nullptr);
    parent->AddChild(child1);
    parent->AddChild(child2);
    ASSERT_EQ(parent->GetChildCount(), 2u);
    EXPECT_EQ(parent->GetChild(0), child1);
    EXPECT_EQ(parent->GetChild(1), child2);
}

// ==================== AddChild: Case 1 (self-reference) ====================

/**
 * @tc.name: AddChildSelfReference001
 * @tc.desc: Test AddChild with self is rejected and parent state unchanged
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHoverVirtualNodeUtilsTest, AddChildSelfReference001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. node attempts to add itself as a child
     * @tc.expected: rejection recorded; node remains its own parent (none) and has no children
     */
    auto node = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(node, nullptr);
    node->SetNodeId(TEST_NODE_ID_ROOT);
    node->AddChild(node);
    EXPECT_FALSE(node->HasChildren());
    EXPECT_EQ(node->GetChildCount(), 0u);
    EXPECT_EQ(node->GetParent(), nullptr);
}

// ==================== AddChild: Case 2 (this is ancestor of child) ====================

/**
 * @tc.name: AddChildThisIsDirectParent001
 * @tc.desc: Test AddChild rejects duplicate direct child (this is direct parent)
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHoverVirtualNodeUtilsTest, AddChildThisIsDirectParent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. parent adds child, then attempts to add the same child again
     * @tc.expected: second AddChild rejected; children list still has exactly one entry
     */
    auto parent = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    auto child = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(parent, nullptr);
    ASSERT_NE(child, nullptr);
    parent->SetNodeId(TEST_NODE_ID_ROOT);
    child->SetNodeId(TEST_NODE_ID_CHILD);
    parent->AddChild(child);
    ASSERT_EQ(parent->GetChildCount(), 1u);
    parent->AddChild(child);
    EXPECT_EQ(parent->GetChildCount(), 1u);
    EXPECT_EQ(child->GetParent(), parent);
}

/**
 * @tc.name: AddChildThisIsGrandparent001
 * @tc.desc: Test AddChild rejects when this is grandparent of child (multi-level Case 2)
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHoverVirtualNodeUtilsTest, AddChildThisIsGrandparent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build chain root -> mid -> leaf, then root->AddChild(leaf)
     * @tc.expected: rejected; leaf's parent remains mid; root still has only mid as child
     */
    auto root = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    auto mid = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    auto leaf = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(root, nullptr);
    ASSERT_NE(mid, nullptr);
    ASSERT_NE(leaf, nullptr);
    root->SetNodeId(TEST_NODE_ID_ROOT);
    mid->SetNodeId(TEST_NODE_ID_CHILD);
    leaf->SetNodeId(TEST_NODE_ID_GRANDCHILD);
    root->AddChild(mid);
    mid->AddChild(leaf);
    ASSERT_EQ(root->GetChildCount(), 1u);

    root->AddChild(leaf);
    EXPECT_EQ(root->GetChildCount(), 1u);
    EXPECT_EQ(root->GetChild(0), mid);
    EXPECT_EQ(leaf->GetParent(), mid);
    EXPECT_EQ(mid->GetChildCount(), 1u);
}

/**
 * @tc.name: AddChildThisIsGreatGrandparent001
 * @tc.desc: Test AddChild rejects when this is great-grandparent of child (deep Case 2)
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHoverVirtualNodeUtilsTest, AddChildThisIsGreatGrandparent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build chain a -> b -> c -> d, then a->AddChild(d)
     * @tc.expected: rejected; tree structure unchanged
     */
    auto a = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    auto b = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    auto c = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    auto d = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(a, nullptr);
    a->SetNodeId(TEST_NODE_ID_ROOT);
    b->SetNodeId(TEST_NODE_ID_CHILD);
    c->SetNodeId(TEST_NODE_ID_GRANDCHILD);
    d->SetNodeId(TEST_NODE_ID_GRANDGRANDCHILD);
    a->AddChild(b);
    b->AddChild(c);
    c->AddChild(d);

    a->AddChild(d);
    EXPECT_EQ(a->GetChildCount(), 1u);
    EXPECT_EQ(a->GetChild(0), b);
    EXPECT_EQ(d->GetParent(), c);
    EXPECT_EQ(c->GetChildCount(), 1u);
}

// ==================== AddChild: Case 3 (child is ancestor of this) ====================

/**
 * @tc.name: AddChildChildIsDirectParent001
 * @tc.desc: Test AddChild rejects when child is the direct parent of this (would create cycle)
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHoverVirtualNodeUtilsTest, AddChildChildIsDirectParent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. parent->AddChild(child), then child->AddChild(parent)
     * @tc.expected: second AddChild rejected; parent's parent remains nullptr; child's parent remains parent
     */
    auto parent = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    auto child = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(parent, nullptr);
    ASSERT_NE(child, nullptr);
    parent->SetNodeId(TEST_NODE_ID_ROOT);
    child->SetNodeId(TEST_NODE_ID_CHILD);
    parent->AddChild(child);
    ASSERT_EQ(child->GetParent(), parent);

    child->AddChild(parent);
    EXPECT_EQ(parent->GetParent(), nullptr);
    EXPECT_EQ(child->GetChildCount(), 0u);
    EXPECT_EQ(parent->GetChildCount(), 1u);
    EXPECT_EQ(parent->GetChild(0), child);
}

/**
 * @tc.name: AddChildChildIsGrandparent001
 * @tc.desc: Test AddChild rejects when child is grandparent of this (multi-level Case 3)
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHoverVirtualNodeUtilsTest, AddChildChildIsGrandparent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build chain root -> mid -> leaf, then leaf->AddChild(root)
     * @tc.expected: rejected; all parent_ pointers unchanged
     */
    auto root = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    auto mid = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    auto leaf = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(root, nullptr);
    ASSERT_NE(mid, nullptr);
    ASSERT_NE(leaf, nullptr);
    root->SetNodeId(TEST_NODE_ID_ROOT);
    mid->SetNodeId(TEST_NODE_ID_CHILD);
    leaf->SetNodeId(TEST_NODE_ID_GRANDCHILD);
    root->AddChild(mid);
    mid->AddChild(leaf);

    leaf->AddChild(root);
    EXPECT_EQ(root->GetParent(), nullptr);
    EXPECT_EQ(mid->GetParent(), root);
    EXPECT_EQ(leaf->GetParent(), mid);
    EXPECT_EQ(leaf->GetChildCount(), 0u);
    EXPECT_EQ(root->GetChildCount(), 1u);
    EXPECT_EQ(mid->GetChildCount(), 1u);
}

// ==================== AddChild: cross-subtree (no false positives) ====================

/**
 * @tc.name: AddChildSiblingSubtree001
 * @tc.desc: Test AddChild allows adding node from a different subtree (no false-positive cycle)
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHoverVirtualNodeUtilsTest, AddChildSiblingSubtree001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build tree1: root1 -> a; tree2: root2 -> b
     * @tc.steps: step2. a->AddChild(b)
     * @tc.expected: operation allowed; b's parent becomes a; a has one child
     */
    auto root1 = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    auto a = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    auto root2 = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    auto b = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(root1, nullptr);
    ASSERT_NE(a, nullptr);
    ASSERT_NE(root2, nullptr);
    ASSERT_NE(b, nullptr);
    root1->SetNodeId(TEST_NODE_ID_ROOT);
    a->SetNodeId(TEST_NODE_ID_CHILD);
    root2->SetNodeId(TEST_NODE_ID_UNRELATED);
    b->SetNodeId(TEST_NODE_ID_GRANDCHILD);
    root1->AddChild(a);
    root2->AddChild(b);

    a->AddChild(b);
    EXPECT_EQ(a->GetChildCount(), 1u);
    EXPECT_EQ(a->GetChild(0), b);
    EXPECT_EQ(b->GetParent(), a);
}

// ==================== AddChild: stack-overflow regression (deep chain) ====================

/**
 * @tc.name: AddChildDeepChainNoOverflow001
 * @tc.desc: Test AddChild does not overflow when child chain back to this is very deep
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHoverVirtualNodeUtilsTest, AddChildDeepChainNoOverflow001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a long chain root -> n1 -> n2 -> ... -> n99
     * @tc.steps: step2. attempt root->AddChild(tail)
     * @tc.expected: detection terminates normally without crash; rejection recorded
     */
    auto root = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(root, nullptr);
    root->SetNodeId(0);
    auto current = root;
    for (int32_t i = 1; i <= DEPTH; ++i) {
        auto node = AceType::MakeRefPtr<VirtualAccessibilityNode>();
        ASSERT_NE(node, nullptr);
        node->SetNodeId(i);
        current->AddChild(node);
        current = node;
    }
    auto tail = current;

    root->AddChild(tail);
    EXPECT_EQ(root->GetChildCount(), 1u);
    EXPECT_EQ(tail->GetParent()->GetNodeId(), DEPTH - 1);
}

// ==================== RemoveChild / ClearChildren preserve cycle invariants ====================

/**
 * @tc.name: ReaddAfterRemove001
 * @tc.desc: Test that after RemoveChild, the same child can be re-added to another parent
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHoverVirtualNodeUtilsTest, ReaddAfterRemove001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. parentA adds child; parentA removes child; parentB adds same child
     * @tc.expected: child successfully migrates from parentA to parentB
     */
    auto parentA = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    auto parentB = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    auto child = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(parentA, nullptr);
    ASSERT_NE(parentB, nullptr);
    ASSERT_NE(child, nullptr);
    parentA->SetNodeId(TEST_NODE_ID_ROOT);
    parentB->SetNodeId(TEST_NODE_ID_UNRELATED);
    child->SetNodeId(TEST_NODE_ID_CHILD);
    parentA->AddChild(child);
    ASSERT_EQ(child->GetParent(), parentA);

    parentA->RemoveChild(child);
    EXPECT_EQ(parentA->GetChildCount(), 0u);
    EXPECT_EQ(child->GetParent(), nullptr);

    parentB->AddChild(child);
    EXPECT_EQ(parentB->GetChildCount(), 1u);
    EXPECT_EQ(child->GetParent(), parentB);
}

// ==================== FindNodeById / TraverseChildren should not infinite-loop ====================

/**
 * @tc.name: FindNodeByIdBasic001
 * @tc.desc: Test FindNodeById locates node by id in a normal tree
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHoverVirtualNodeUtilsTest, FindNodeByIdBasic001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build root -> child -> grandchild, search for each id
     * @tc.expected: each search returns the correct node
     */
    auto root = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    auto child = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    auto grandchild = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(root, nullptr);
    ASSERT_NE(child, nullptr);
    ASSERT_NE(grandchild, nullptr);
    root->SetNodeId(TEST_NODE_ID_ROOT);
    child->SetNodeId(TEST_NODE_ID_CHILD);
    grandchild->SetNodeId(TEST_NODE_ID_GRANDCHILD);
    root->AddChild(child);
    child->AddChild(grandchild);

    EXPECT_EQ(root->FindNodeById(TEST_NODE_ID_ROOT), root);
    EXPECT_EQ(root->FindNodeById(TEST_NODE_ID_CHILD), child);
    EXPECT_EQ(root->FindNodeById(TEST_NODE_ID_GRANDCHILD), grandchild);
    EXPECT_EQ(root->FindNodeById(TEST_NODE_ID_UNRELATED), nullptr);
}

// ==================== CloneTree: new fields added in this commit ====================

/**
 * @tc.name: CloneTreeCopiesNewFields001
 * @tc.desc: Test CloneTree copies the newly added fields (Text, AccessibilityRole, Clickable)
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHoverVirtualNodeUtilsTest, CloneTreeCopiesNewFields001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set Text, AccessibilityRole, Clickable on the source node
     * @tc.steps: step2. clone the tree
     * @tc.expected: cloned root carries identical Text, AccessibilityRole and Clickable values
     */
    auto src = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(src, nullptr);
    src->SetText(TEXT);
    src->SetAccessibilityRole(ROLE);
    src->SetClickable(true);

    auto clone = src->CloneTree();
    ASSERT_NE(clone, nullptr);
    EXPECT_EQ(clone->GetText(), TEXT);
    EXPECT_EQ(clone->GetAccessibilityRole(), ROLE);
    EXPECT_TRUE(clone->GetClickable());
}

/**
 * @tc.name: CloneTreeCopiesAllFields001
 * @tc.desc: Test CloneTree copies all properties of the root node (existing + new)
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHoverVirtualNodeUtilsTest, CloneTreeCopiesAllFields001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. populate every property on the source node and set its rect
     * @tc.steps: step2. clone the tree
     * @tc.expected: every property and the rect are equal between source and clone
     */
    auto src = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(src, nullptr);
    src->SetNodeId(TEST_NODE_ID_ROOT);
    src->SetText("text");
    src->SetAccessibilityText("accText");
    src->SetAccessibilityLevel("yes");
    src->SetAccessibilityGroup(true);
    src->SetRole("role");
    src->SetAccessibilityRole("accRole");
    src->SetCheckable(true);
    src->SetChecked(true);
    src->SetEnabled(false);
    src->SetSelected(true);
    src->SetClickable(true);
    src->SetRect(10, 20, 100, 200);

    auto clone = src->CloneTree();
    ASSERT_NE(clone, nullptr);
    EXPECT_EQ(clone->GetNodeId(), TEST_NODE_ID_ROOT);
    EXPECT_EQ(clone->GetText(), "text");
    EXPECT_EQ(clone->GetAccessibilityText(), "accText");
    EXPECT_EQ(clone->GetAccessibilityLevel(), "yes");
    EXPECT_TRUE(clone->GetAccessibilityGroup());
    EXPECT_EQ(clone->GetRole(), "role");
    EXPECT_EQ(clone->GetAccessibilityRole(), "accRole");
    EXPECT_TRUE(clone->GetCheckable());
    EXPECT_TRUE(clone->GetChecked());
    EXPECT_FALSE(clone->GetEnabled());
    EXPECT_TRUE(clone->GetSelected());
    EXPECT_TRUE(clone->GetClickable());
    EXPECT_EQ(clone->GetLeft(), 10);
    EXPECT_EQ(clone->GetTop(), 20);
    EXPECT_EQ(clone->GetWidth(), 100);
    EXPECT_EQ(clone->GetHeight(), 200);
}

/**
 * @tc.name: CloneTreeRecursion001
 * @tc.desc: Test CloneTree recursively clones the whole subtree preserving structure
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHoverVirtualNodeUtilsTest, CloneTreeRecursion001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build root -> child -> grandchild, give each a distinct Text
     * @tc.steps: step2. clone root
     * @tc.expected: clone has the same 2-level depth; each cloned node copies its Text and parent links
     */
    auto root = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    auto child = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    auto grandchild = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(root, nullptr);
    ASSERT_NE(child, nullptr);
    ASSERT_NE(grandchild, nullptr);
    root->SetNodeId(TEST_NODE_ID_ROOT);
    child->SetNodeId(TEST_NODE_ID_CHILD);
    grandchild->SetNodeId(TEST_NODE_ID_GRANDCHILD);
    root->SetText("root");
    child->SetText("child");
    grandchild->SetText("grandchild");
    root->AddChild(child);
    child->AddChild(grandchild);

    auto clone = root->CloneTree();
    ASSERT_NE(clone, nullptr);
    ASSERT_EQ(clone->GetChildCount(), 1u);
    auto cloneChild = clone->GetChild(0);
    ASSERT_NE(cloneChild, nullptr);
    EXPECT_EQ(cloneChild->GetText(), "child");
    EXPECT_EQ(cloneChild->GetParent(), clone);
    ASSERT_EQ(cloneChild->GetChildCount(), 1u);
    auto cloneGrand = cloneChild->GetChild(0);
    ASSERT_NE(cloneGrand, nullptr);
    EXPECT_EQ(cloneGrand->GetText(), "grandchild");
    EXPECT_EQ(cloneGrand->GetParent(), cloneChild);
}

/**
 * @tc.name: CloneTreeIsDeepCopy001
 * @tc.desc: Test CloneTree produces an independent tree; mutating clone does not affect source
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHoverVirtualNodeUtilsTest, CloneTreeIsDeepCopy001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build root -> child and clone it
     * @tc.steps: step2. mutate fields on the cloned nodes and add a new child to the clone
     * @tc.expected: source tree is unchanged (values and child count preserved)
     */
    auto root = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    auto child = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(root, nullptr);
    ASSERT_NE(child, nullptr);
    root->SetNodeId(TEST_NODE_ID_ROOT);
    child->SetNodeId(TEST_NODE_ID_CHILD);
    root->SetText("original");
    child->SetText("original-child");
    root->AddChild(child);

    auto clone = root->CloneTree();
    ASSERT_NE(clone, nullptr);
    clone->SetText("mutated");
    auto cloneChild = clone->GetChild(0);
    ASSERT_NE(cloneChild, nullptr);
    cloneChild->SetText("mutated-child");
    auto extra = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(extra, nullptr);
    clone->AddChild(extra);

    EXPECT_EQ(root->GetText(), "original");
    ASSERT_EQ(root->GetChildCount(), 1u);
    EXPECT_EQ(root->GetChild(0)->GetText(), "original-child");
    EXPECT_EQ(clone->GetText(), "mutated");
    EXPECT_EQ(clone->GetChildCount(), 2u);
}

/**
 * @tc.name: CloneTreeEmpty001
 * @tc.desc: Test CloneTree on a leaf node with no children returns a childless clone
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHoverVirtualNodeUtilsTest, CloneTreeEmpty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a leaf node and clone it
     * @tc.expected: clone is non-null, has no children and no parent
     */
    auto leaf = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(leaf, nullptr);
    leaf->SetNodeId(TEST_NODE_ID_ROOT);

    auto clone = leaf->CloneTree();
    ASSERT_NE(clone, nullptr);
    EXPECT_FALSE(clone->HasChildren());
    EXPECT_EQ(clone->GetChildCount(), 0u);
    EXPECT_EQ(clone->GetParent(), nullptr);
    EXPECT_EQ(clone->GetNodeId(), TEST_NODE_ID_ROOT);
}

// ==================== CustomAccessibilityProperty: new getters/setters ====================

/**
 * @tc.name: CustomPropertyText001
 * @tc.desc: Test SetText/GetText roundtrip and default empty value
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHoverVirtualNodeUtilsTest, CustomPropertyText001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. check default value, then set and get a text
     * @tc.expected: default is empty; getter returns the value that was set
     */
    auto node = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(node, nullptr);
    EXPECT_TRUE(node->GetText().empty());

    node->SetText(TEXT);
    EXPECT_EQ(node->GetText(), TEXT);
}

/**
 * @tc.name: CustomPropertyAccessibilityRole001
 * @tc.desc: Test SetAccessibilityRole/GetAccessibilityRole roundtrip and default empty value
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHoverVirtualNodeUtilsTest, CustomPropertyAccessibilityRole001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. check default value, then set and get an accessibility role
     * @tc.expected: default is empty; getter returns the value that was set
     */
    auto node = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(node, nullptr);
    EXPECT_TRUE(node->GetAccessibilityRole().empty());

    node->SetAccessibilityRole(ROLE);
    EXPECT_EQ(node->GetAccessibilityRole(), ROLE);
}

/**
 * @tc.name: CustomPropertyClickable001
 * @tc.desc: Test SetClickable/GetClickable roundtrip and default false value
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHoverVirtualNodeUtilsTest, CustomPropertyClickable001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. check default value, then toggle clickable true and false
     * @tc.expected: default is false; getter reflects each set value
     */
    auto node = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(node, nullptr);
    EXPECT_FALSE(node->GetClickable());

    node->SetClickable(true);
    EXPECT_TRUE(node->GetClickable());

    node->SetClickable(false);
    EXPECT_FALSE(node->GetClickable());
}

/**
 * @tc.name: CustomPropertySupprtAction001
 * @tc.desc: Test SetSupprtAction/GetSupportAction roundtrip and default zero value
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHoverVirtualNodeUtilsTest, CustomPropertySupprtAction001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. check default value, then set and get a support action bitmask
     * @tc.expected: default is 0; getter returns the value that was set
     */
    auto node = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetSupportAction(), 0ull);

    node->SetSupprtAction(ACTIONS);
    EXPECT_EQ(node->GetSupportAction(), ACTIONS);
}

} // namespace OHOS::Ace::NG
