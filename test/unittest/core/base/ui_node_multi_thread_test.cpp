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

#include <memory>
#include <ostream>
#include <utility>

#include "gtest/gtest.h"

#define protected public
#define private public

#include "core/common/multi_thread_build_manager.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class UINodeMultiThreadTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void UINodeMultiThreadTest::SetUpTestSuite() {}

void UINodeMultiThreadTest::TearDownTestSuite() {}

/**
 * @tc.name: MarkNodeTreeNotFree001
 * @tc.desc: Test MarkNodeTreeNotFree
 * @tc.type: FUNC
 */
HWTEST_F(UINodeMultiThreadTest, MarkNodeTreeNotFree001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create safe node
     */
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(true);
    auto safeNode1 =
        FrameNode::CreateFrameNode("safe", 1, AceType::MakeRefPtr<Pattern>(), true);
    safeNode1->setIsCNode(true);
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(false);
    EXPECT_EQ(safeNode1->isFree_, true);
    /**
     * @tc.steps: step2. safe node call MarkNodeTreeNotFree
     * @tc.expected: safe node is not free
     */
    safeNode1->MarkNodeTreeNotFree();
    EXPECT_EQ(safeNode1->isFree_, false);
}

/**
 * @tc.name: MarkNodeTreeNotFree002
 * @tc.desc: Test MarkNodeTreeNotFree
 * @tc.type: FUNC
 */
HWTEST_F(UINodeMultiThreadTest, MarkNodeTreeNotFree002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create safe node tree
     */
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(true);
    auto safeNode1 =
        FrameNode::CreateFrameNode("safe", 1, AceType::MakeRefPtr<Pattern>(), true);
    safeNode1->setIsCNode(true);
    auto safeNode2 =
        FrameNode::CreateFrameNode("safe", 2, AceType::MakeRefPtr<Pattern>(), true);
    safeNode2->setIsCNode(true);
    safeNode1->AddChild(safeNode2);
    EXPECT_EQ(safeNode1->isFree_, true);
    EXPECT_EQ(safeNode2->isFree_, true);
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(false);

    /**
     * @tc.steps: step2. safe node tree call MarkNodeTreeNotFree
     * @tc.expected: safe node tree is not free
     */
    safeNode2->MarkNodeTreeNotFree();
    EXPECT_EQ(safeNode1->isFree_, false);
    EXPECT_EQ(safeNode2->isFree_, false);
}

/**
 * @tc.name: MarkNodeTreeNotFree003
 * @tc.desc: Test MarkNodeTreeNotFree
 * @tc.type: FUNC
 */
HWTEST_F(UINodeMultiThreadTest, MarkNodeTreeNotFree003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create safe node
     */
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(true);
    auto safeNode1 =
        FrameNode::CreateFrameNode("safe", 1, AceType::MakeRefPtr<Pattern>(), true);
    safeNode1->setIsCNode(true);
    auto safeNode2 =
        FrameNode::CreateFrameNode("safe", 2, AceType::MakeRefPtr<Pattern>(), true);
    safeNode2->setIsCNode(true);
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(false);
    /**
     * @tc.steps: step2. create unsafe node
     */
    auto unSafeNode1 =
        FrameNode::CreateFrameNode("unsafe", 3, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step3. safe node add unsafe node child
     * @tc.expected: safe node is not free
     */
    safeNode2->AddChild(unSafeNode1);
    EXPECT_EQ(safeNode2->isFree_, false);

    /**
     * @tc.steps: step4. unsafe node add safe node child
     * @tc.expected: safe node is not free
     */
    unSafeNode1->AddChild(safeNode1);
    EXPECT_EQ(safeNode1->isFree_, false);
}

/**
 * @tc.name: MarkNodeNotFree001
 * @tc.desc: Test MarkNodeNotFree
 * @tc.type: FUNC
 */
HWTEST_F(UINodeMultiThreadTest, MarkNodeNotFree001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create safe node tree
     */
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(true);
    auto safeNode1 =
        FrameNode::CreateFrameNode("safe", 1, AceType::MakeRefPtr<Pattern>(), true);
    safeNode1->setIsCNode(true);
    auto safeNode2 =
        FrameNode::CreateFrameNode("safe", 2, AceType::MakeRefPtr<Pattern>(), true);
    safeNode2->setIsCNode(true);
    safeNode1->AddChild(safeNode2);
    EXPECT_EQ(safeNode1->isFree_, true);
    EXPECT_EQ(safeNode2->isFree_, true);
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(false);

    /**
     * @tc.steps: step2. safe node tree call MarkNodeNotFree
     * @tc.expected: safe node tree is not free
     */
    safeNode1->MarkNodeNotFree();
    EXPECT_EQ(safeNode1->isFree_, false);
    EXPECT_EQ(safeNode2->isFree_, false);
}

/**
 * @tc.name: CheckThreadSafeNodeTree001
 * @tc.desc: Test CheckThreadSafeNodeTree
 * @tc.type: FUNC
 */
HWTEST_F(UINodeMultiThreadTest, CheckThreadSafeNodeTree001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create safe node tree
     */
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(true);
    auto safeNode1 =
        FrameNode::CreateFrameNode("safe", 1, AceType::MakeRefPtr<Pattern>(), false);
    safeNode1->setIsCNode(true);
    auto safeNode2 =
        FrameNode::CreateFrameNode("safe", 2, AceType::MakeRefPtr<Pattern>(), false);
    safeNode2->setIsCNode(true);
    safeNode1->AddChild(safeNode2);
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(false);

    /**
     * @tc.steps: step2. safe node tree call CheckThreadSafeNodeTree
     * @tc.expected: return true
     */
    EXPECT_EQ(safeNode1->CheckThreadSafeNodeTree(), true);

    /**
     * @tc.steps: step3. safe node tree call CheckThreadSafeNodeTree
     * @tc.expected: return true
     */
    auto unSafeNode1 =
        FrameNode::CreateFrameNode("unsafe", 3, AceType::MakeRefPtr<Pattern>(), false);
    safeNode2->AddChild(unSafeNode1);
    EXPECT_EQ(safeNode1->CheckThreadSafeNodeTree(), true);

    /**
     * @tc.steps: step4. unsafe node tree call CheckThreadSafeNodeTree
     * @tc.expected: return false
     */
    auto unSafeNode2 =
        FrameNode::CreateFrameNode("unsafe", 4, AceType::MakeRefPtr<Pattern>(), false);
    unSafeNode2->setIsCNode(true);
    safeNode2->AddChild(unSafeNode2);
    EXPECT_EQ(safeNode1->CheckThreadSafeNodeTree(), false);
}

/**
 * @tc.name: MarkNodeTreeFree001
 * @tc.desc: Test MarkNodeTreeFree
 * @tc.type: FUNC
 */
HWTEST_F(UINodeMultiThreadTest, MarkNodeTreeFree001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create safe node tree
     */
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(true);
    auto safeNode1 =
        FrameNode::CreateFrameNode("safe", 1, AceType::MakeRefPtr<Pattern>(), true);
    safeNode1->setIsCNode(true);
    auto safeNode2 =
        FrameNode::CreateFrameNode("safe", 2, AceType::MakeRefPtr<Pattern>(), true);
    safeNode2->setIsCNode(true);
    safeNode1->AddChild(safeNode2);
    EXPECT_EQ(safeNode1->isFree_, true);
    EXPECT_EQ(safeNode2->isFree_, true);
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(false);
    /**
     * @tc.steps: step2. create unsafe node
     */
    auto unSafeNode1 =
        FrameNode::CreateFrameNode("unsafe", 3, AceType::MakeRefPtr<Pattern>(), true);
    unSafeNode1->AddChild(safeNode1);

    /**
     * @tc.steps: step3. unsafe node call MarkNodeTreeFree
     * @tc.expected: safe node is not free
     */
    unSafeNode1->MarkNodeTreeFree();
    EXPECT_EQ(safeNode1->isFree_, false);
    EXPECT_EQ(safeNode2->isFree_, false);

    /**
     * @tc.steps: step4. unsafe node call MarkNodeTreeFree
     * @tc.expected: safe node is not free
     */
    safeNode1->MarkNodeTreeFree(true);
    EXPECT_EQ(safeNode1->isFree_, false);
    EXPECT_EQ(safeNode2->isFree_, false);

    /**
     * @tc.steps: step5. safe node call MarkNodeTreeFree
     * @tc.expected: safe node is free
     */
    unSafeNode1->RemoveChild(safeNode1);
    safeNode1->MarkNodeTreeFree(true);
    EXPECT_EQ(safeNode1->isFree_, true);
    EXPECT_EQ(safeNode2->isFree_, true);
}

/**
 * @tc.name: MarkNodeFree001
 * @tc.desc: Test MarkNodeFree
 * @tc.type: FUNC
 */
HWTEST_F(UINodeMultiThreadTest, MarkNodeFree001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create safe node tree
     */
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(true);
    auto safeNode1 =
        FrameNode::CreateFrameNode("safe", 1, AceType::MakeRefPtr<Pattern>(), true);
    safeNode1->setIsCNode(true);
    auto safeNode2 =
        FrameNode::CreateFrameNode("safe", 2, AceType::MakeRefPtr<Pattern>(), true);
    safeNode2->setIsCNode(true);
    safeNode1->AddChild(safeNode2);
    EXPECT_EQ(safeNode1->isFree_, true);
    EXPECT_EQ(safeNode2->isFree_, true);
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(false);
    safeNode1->isFree_ = false;
    safeNode2->isFree_ = false;

    /**
     * @tc.steps: step2. unsafe node call MarkNodeFree
     * @tc.expected: safe node is not free
     */
    safeNode1->MarkNodeFree();
    EXPECT_EQ(safeNode1->isFree_, true);
    EXPECT_EQ(safeNode2->isFree_, true);
}

/**
 * @tc.name: PostAfterAttachMainTreeTask001
 * @tc.desc: Test PostAfterAttachMainTreeTask
 * @tc.type: FUNC
 */
HWTEST_F(UINodeMultiThreadTest, PostAfterAttachMainTreeTask001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create safe node
     */
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(true);
    auto safeNode1 =
        FrameNode::CreateFrameNode("safe", 1, AceType::MakeRefPtr<Pattern>(), true);
    safeNode1->setIsCNode(true);
    EXPECT_EQ(safeNode1->isFree_, true);
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(false);

    /**
     * @tc.steps: step2. safe node call PostAfterAttachMainTreeTask
     * @tc.expected: post task success
     */
    safeNode1->PostAfterAttachMainTreeTask([]() { return; });
    EXPECT_EQ(safeNode1->afterAttachMainTreeTasks_.size(), 1);

    /**
     * @tc.steps: step3. unsafe node call PostAfterAttachMainTreeTask
     * @tc.expected: post task failed
     */
    safeNode1->isFree_ = false;
    safeNode1->PostAfterAttachMainTreeTask([]() { return; });
    EXPECT_EQ(safeNode1->afterAttachMainTreeTasks_.size(), 1);

    /**
     * @tc.steps: step4. safe node call PostAfterAttachMainTreeTask when running task
     * @tc.expected: post task failed
     */
    safeNode1->isFree_ = true;
    safeNode1->isRunningPendingUnsafeTask_ = true;
    safeNode1->PostAfterAttachMainTreeTask([]() { return; });
    EXPECT_EQ(safeNode1->afterAttachMainTreeTasks_.size(), 1);

    /**
     * @tc.steps: step5. safe node call ExecuteAfterAttachMainTreeTasks
     * @tc.expected: execute task success
     */
    safeNode1->ExecuteAfterAttachMainTreeTasks();
    EXPECT_EQ(safeNode1->afterAttachMainTreeTasks_.size(), 0);
}


/**
 * @tc.name: DoAddChildFreeState001
 * @tc.desc: Test DoAddChild with parent not free and child free
 * @tc.type: FUNC
 */
HWTEST_F(UINodeMultiThreadTest, DoAddChildFreeState001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create parent and child nodes
     */
    auto parent = FrameNode::CreateFrameNode("unsafe", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto child = FrameNode::CreateFrameNode("safe", 2, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. set parent not free, child free
     */
    parent->SetIsFree(false);
    child->SetIsFree(true);

    /**
     * @tc.steps: step3. add child to parent using DoAddChild
     */
    auto it = parent->children_.begin();
    parent->DoAddChild(it, child, false, false);

    /**
     * @tc.expected: child should be marked not free after insertion
     */
    EXPECT_FALSE(child->IsFree());
    EXPECT_EQ(parent->children_.size(), 1);
    parent->Clean();
}
} // namespace OHOS::Ace::NG