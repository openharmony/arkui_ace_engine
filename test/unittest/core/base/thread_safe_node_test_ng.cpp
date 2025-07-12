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

#define protected public
#define private public

#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/common/multi_thread_build_manager.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/pattern.h"
#include "frameworks/core/pipeline/base/element_register_multi_thread.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class ThreadSafeNodeTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void ThreadSafeNodeTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void ThreadSafeNodeTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: ThreadSafeNodeTestNg001
 * @tc.desc: Test AddUINodeMultiThread Repeated
 * @tc.type: FUNC
 */
HWTEST_F(ThreadSafeNodeTestNg, ThreadSafeNodeTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create thread safe uinode
     */
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(true);
    auto frameNode = AceType::MakeRefPtr<FrameNode>("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(false);

    /**
     * @tc.steps: step2. thread safe uinode add to ElementRegister
     * @tc.expected: add success
     */
    EXPECT_EQ(ElementRegisterMultiThread::GetInstance()->AddUINodeMultiThread(frameNode), true);

    /**
     * @tc.steps: step3. thread safe uinode add to ElementRegister again
     * @tc.expected: add failed
     */
    EXPECT_EQ(ElementRegisterMultiThread::GetInstance()->AddUINodeMultiThread(frameNode), false);
}

/**
 * @tc.name: ThreadSafeNodeTestNg002
 * @tc.desc: Test GetThreadSafeNodeById
 * @tc.type: FUNC
 */
HWTEST_F(ThreadSafeNodeTestNg, ThreadSafeNodeTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create thread safe uinode
     */
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(true);
    auto frameNode =
        FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(false);
    EXPECT_EQ(ElementRegisterMultiThread::GetInstance()->AddUINodeMultiThread(frameNode), true);

    /**
     * @tc.steps: step2. get the thread safe node which id is 1 from ElementRegister
     * @tc.expected: get success
     */
    EXPECT_EQ(ElementRegisterMultiThread::GetInstance()->GetThreadSafeNodeById(1), true);

    /**
     * @tc.steps: step3. get the thread safe node which id is ElementRegister::UndefinedElementId from ElementRegister
     * @tc.expected: get failed
     */
    EXPECT_EQ(
         ElementRegisterMultiThread::GetInstance()->GetThreadSafeNodeById(ElementRegister::UndefinedElementId), false);
}

/**
 * @tc.name: ThreadSafeNodeTestNg003
 * @tc.desc: Test RemoveThreadSafeNode
 * @tc.type: FUNC
 */
HWTEST_F(ThreadSafeNodeTestNg, ThreadSafeNodeTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create thread safe uinode
     */
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(true);
    auto frameNode =
        FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(false);
    EXPECT_EQ(ElementRegisterMultiThread::GetInstance()->AddUINodeMultiThread(frameNode), true);

    /**
     * @tc.steps: step2. remove the thread safe node which id is 1 from ElementRegister
     * @tc.expected: remove success
     */
    EXPECT_EQ(ElementRegisterMultiThread::GetInstance()->RemoveThreadSafeNode(1), true);

    /**
     * @tc.steps: step3. remove the thread safe node which
     * id is ElementRegister::UndefinedElementId from ElementRegister
     * @tc.expected: remove failed
     */
    EXPECT_EQ(
        ElementRegisterMultiThread::GetInstance()->RemoveThreadSafeNode(ElementRegister::UndefinedElementId), false);
}

/**
 * @tc.name: ThreadSafeNodeTestNg004
 * @tc.desc: Test thread safe node RebuildRenderContextTree.
 * @tc.type: FUNC
 */
HWTEST_F(ThreadSafeNodeTestNg, ThreadSafeNodeTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create thread safe uinode
     */
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(true);
    auto frameNode =
        FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(false);

    /**
     * @tc.steps: step2. thread safe uinode RebuildRenderContextTree
     * @tc.expected: rebuild success
     */
    int32_t taskSize = frameNode->afterAttachMainTreeTasks_.size();
    frameNode->RebuildRenderContextTree();
    EXPECT_EQ(frameNode->afterAttachMainTreeTasks_.size(), taskSize + 1);
}

/**
 * @tc.name: ThreadSafeNodeTestNg005
 * @tc.desc: Test thread safe node MarkNeedRender.
 * @tc.type: FUNC
 */
HWTEST_F(ThreadSafeNodeTestNg, ThreadSafeNodeTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create thread safe uinode
     */
    auto context = MockPipelineContext::GetCurrent();
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(true);
    auto frameNode =
        FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(false);
    frameNode->context_ = AceType::RawPtr(context);
    frameNode->isRenderDirtyMarked_ = false;
    frameNode->isLayoutDirtyMarked_ = false;

    /**
     * @tc.steps: step2. thread safe uinode MarkNeedRender
     * @tc.expected: mark success
     */
    int32_t taskSize = frameNode->afterAttachMainTreeTasks_.size();
    frameNode->MarkNeedRender(true);
    EXPECT_EQ(frameNode->afterAttachMainTreeTasks_.size(), taskSize + 1);

    /**
     * @tc.steps: step3. create not thread safe uinode
     */
    auto frameNode2 =
        FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode2->context_ = AceType::RawPtr(context);
    frameNode2->isRenderDirtyMarked_ = false;
    frameNode2->isLayoutDirtyMarked_ = false;

    /**
     * @tc.steps: step4. not thread safe uinode MarkNeedRender
     * @tc.expected: mark success
     */
    taskSize = frameNode2->afterAttachMainTreeTasks_.size();
    frameNode2->MarkNeedRender(true);
    EXPECT_EQ(frameNode2 ->afterAttachMainTreeTasks_.size(), taskSize);
}

/**
 * @tc.name: ThreadSafeNodeTestNg006
 * @tc.desc: Test thread safe uinode create.
 * @tc.type: FUNC
 */
HWTEST_F(ThreadSafeNodeTestNg, ThreadSafeNodeTestNg006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create thread safe uinode
     * @tc.expected: create success
     */
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(true);
    auto frameNode =
        FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(false);
    EXPECT_EQ(frameNode->isThreadSafeNode_, true);
    EXPECT_EQ(frameNode->isFree_, true);
}

/**
 * @tc.name: ThreadSafeNodeTestNg007
 * @tc.desc: Test thread safe uinode release
 * @tc.type: FUNC
 */
HWTEST_F(ThreadSafeNodeTestNg, ThreadSafeNodeTestNg007, TestSize.Level1)
{
    bool isUIThread = MultiThreadBuildManager::isUIThread_;
    {
        /**
         * @tc.steps: step1. create thread safe uinode
         */
        MultiThreadBuildManager::SetIsThreadSafeNodeScope(true);
        auto frameNode =
            FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
        MultiThreadBuildManager::SetIsThreadSafeNodeScope(false);
        /**
         * @tc.steps: step2. release thread safe uinode not on ui thread
         * @tc.expected: release success
         */
        MultiThreadBuildManager::isUIThread_ = false;
        EXPECT_EQ(frameNode->isThreadSafeNode_, true);
        EXPECT_EQ(frameNode->isFree_, true);
    }
    {
        /**
         * @tc.steps: step3. create thread safe uinode
         */
        MultiThreadBuildManager::SetIsThreadSafeNodeScope(true);
        auto frameNode =
            FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
        MultiThreadBuildManager::SetIsThreadSafeNodeScope(false);
        /**
         * @tc.steps: step2. release thread safe uinode on ui thread
         * @tc.expected: release success
         */
        MultiThreadBuildManager::isUIThread_ = true;
        EXPECT_EQ(frameNode->isThreadSafeNode_, true);
        EXPECT_EQ(frameNode->isFree_, true);
    }
    MultiThreadBuildManager::isUIThread_ = isUIThread;
}

/**
 * @tc.name: ThreadSafeNodeTestNg0088
 * @tc.desc: Test uinode release
 * @tc.type: FUNC
 */
HWTEST_F(ThreadSafeNodeTestNg, ThreadSafeNodeTestNg008, TestSize.Level1)
{
    bool isUIThread = MultiThreadBuildManager::isUIThread_;
    {
        /**
         * @tc.steps: step1. create not thread safe uinode
         */
        auto frameNode =
            FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
        /**
         * @tc.steps: step2. release not thread safe uinode not on ui thread
         * @tc.expected: release success
         */
        MultiThreadBuildManager::isUIThread_ = false;
        EXPECT_EQ(frameNode->isThreadSafeNode_, false);
        EXPECT_EQ(frameNode->isFree_, false);
    }
    {
        /**
         * @tc.steps: step3. create not thread safe uinode
         */
        auto frameNode =
            FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
        /**
         * @tc.steps: step4. release not thread safe uinode on ui thread
         * @tc.expected: release success
         */
        MultiThreadBuildManager::isUIThread_ = true;
        EXPECT_EQ(frameNode->isThreadSafeNode_, false);
        EXPECT_EQ(frameNode->isFree_, false);
    }
    MultiThreadBuildManager::isUIThread_ = isUIThread;
}

/**
 * @tc.name: ThreadSafeNodeTestNg009
 * @tc.desc: Test thread safe uinode AttachToMainTree.
 * @tc.type: FUNC
 */
HWTEST_F(ThreadSafeNodeTestNg, ThreadSafeNodeTestNg009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create thread safe uinode
     */
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(true);
    auto frameNode =
        FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(false);
    
    /**
     * @tc.steps: step2. thread safe uinode AttachToMainTree and DetachFromMainTree
     * @tc.expected: attach and detach success
     */
    PipelineContext* pipeline = frameNode->GetContextWithCheck();
    frameNode->AttachToMainTree(false, pipeline);
    EXPECT_EQ(frameNode->isFree_, false);
    frameNode->DetachFromMainTree(false, false);
    EXPECT_EQ(frameNode->isFree_, true);
}

/**
 * @tc.name: ThreadSafeNodeTestNg010
 * @tc.desc: Test thread safe uinode DetachFromMainTree.
 * @tc.type: FUNC
 */
HWTEST_F(ThreadSafeNodeTestNg, ThreadSafeNodeTestNg010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create thread safe uinode
     */
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(true);
    auto frameNode =
        FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(false);
    
    /**
     * @tc.steps: step2. thread safe uinode AttachToMainTree and DetachFromMainTree
     * @tc.expected: attach and detach success
     */
    PipelineContext* pipeline = frameNode->GetContextWithCheck();
    frameNode->AttachToMainTree(false, pipeline);
    EXPECT_EQ(frameNode->isFree_, false);
    frameNode->DetachFromMainTree(false, true);
    EXPECT_EQ(frameNode->isFree_, true);
}

/**
 * @tc.name: ThreadSafeNodeTestNg011
 * @tc.desc: Test thread safe uinode tree DetachFromMainTree.
 * @tc.type: FUNC
 */
HWTEST_F(ThreadSafeNodeTestNg, ThreadSafeNodeTestNg011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create thread safe uinode tree
     */
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(true);
    auto frameNode =
        FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto child =
        FrameNode::CreateFrameNode("main", 2, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->AddChild(child);
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(false);
    
    /**
     * @tc.steps: step2. thread safe uinode tree AttachToMainTree and DetachFromMainTree
     * @tc.expected: attach and detach success
     */
    PipelineContext* pipeline = frameNode->GetContextWithCheck();
    frameNode->AttachToMainTree(false, pipeline);
    EXPECT_EQ(frameNode->isFree_, false);
    frameNode->DetachFromMainTree(false, true);
    EXPECT_EQ(frameNode->isFree_, true);
}

/**
 * @tc.name: ThreadSafeNodeTestNg012
 * @tc.desc: Test not thread safe ui node tree DetachFromMainTree.
 * @tc.type: FUNC
 */
HWTEST_F(ThreadSafeNodeTestNg, ThreadSafeNodeTestNg012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create thread safe uinode
     */
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(true);
    auto frameNode =
        FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(false);
    /**
     * @tc.steps: step2. create not thread safe uinode tree
     */
    auto child =
        FrameNode::CreateFrameNode("main", 2, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->AddChild(child);
    /**
     * @tc.steps: step3. not thread safe uinode tree AttachToMainTree and DetachFromMainTree
     * @tc.expected: attach and detach success
     */
    PipelineContext* pipeline = frameNode->GetContextWithCheck();
    frameNode->AttachToMainTree(false, pipeline);
    EXPECT_EQ(frameNode->isFree_, false);
    frameNode->DetachFromMainTree(false, true);
    EXPECT_EQ(frameNode->isFree_, true);
}

/**
 * @tc.name: ThreadSafeNodeTestNg013
 * @tc.desc: Test thread safe node MarkModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(ThreadSafeNodeTestNg, ThreadSafeNodeTestNg013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create thread safe uinode
     */
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(true);
    auto frameNode =
        FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(false);
    /**
     * @tc.steps: step2. thread safe uinode MarkModifyDone
     * @tc.expected: MarkModifyDone success
     */
    int32_t taskSize = frameNode->afterAttachMainTreeTasks_.size();
    frameNode->MarkModifyDone();
    EXPECT_EQ(frameNode->afterAttachMainTreeTasks_.size(), taskSize + 1);
}

/**
 * @tc.name: ThreadSafeNodeTestNg014
 * @tc.desc: Test thread safe node MarkDirtyNode.
 * @tc.type: FUNC
 */
HWTEST_F(ThreadSafeNodeTestNg, ThreadSafeNodeTestNg014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create thread safe uinode
     */
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(true);
    auto frameNode =
        FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(false);
    /**
     * @tc.steps: step2. thread safe uinode MarkDirtyNode
     * @tc.expected: MarkDirtyNode success
     */
    int32_t taskSize = frameNode->afterAttachMainTreeTasks_.size();
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    EXPECT_EQ(frameNode->afterAttachMainTreeTasks_.size(), taskSize + 1);
}

/**
 * @tc.name: ThreadSafeNodeTestNg015
 * @tc.desc: Test thread safe node CheckThreadSafeNodeTree.
 * @tc.type: FUNC
 */
HWTEST_F(ThreadSafeNodeTestNg, ThreadSafeNodeTestNg015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create thread safe uinode
     */
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(true);
    auto frameNode =
        FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(false);
    /**
     * @tc.steps: step2. thread safe uinode CheckThreadSafeNodeTree
     * @tc.expected: CheckThreadSafeNodeTree success
     */
    EXPECT_EQ(frameNode->CheckThreadSafeNodeTree(true), true);
    EXPECT_EQ(frameNode->CheckThreadSafeNodeTree(false), true);
}

/**
 * @tc.name: ThreadSafeNodeTestNg016
 * @tc.desc: Test thread unsafe node CheckThreadSafeNodeTree.
 * @tc.type: FUNC
 */
HWTEST_F(ThreadSafeNodeTestNg, ThreadSafeNodeTestNg016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create thread unsafe uinode
     */
    auto frameNode =
        FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    /**
     * @tc.steps: step2. thread unsafe uinode CheckThreadSafeNodeTree
     * @tc.expected: CheckThreadSafeNodeTree success
     */
    EXPECT_EQ(frameNode->CheckThreadSafeNodeTree(true), false);
    EXPECT_EQ(frameNode->CheckThreadSafeNodeTree(false), false);
}
} // namespace OHOS::Ace::NG