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

#include "gtest/gtest.h"

#define protected public
#define private public

#include "core/common/multi_thread_build_manager.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/pattern.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class UINodeIsolatedThreadTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
    }
    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
    }
};

/**
 * @tc.name: UINodeIsolatedThreadTest_FlagDefaultAndMatchContext001
 * @tc.desc: Test isIsolatedThread_ defaults to false, getter works, and GetContext returns context on match
 * @tc.type: FUNC
 */
HWTEST_F(UINodeIsolatedThreadTest, UINodeIsolatedThreadTest_FlagDefaultAndMatchContext001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);

    auto node = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(node, nullptr);

    EXPECT_FALSE(node->isIsolatedThread_);
    EXPECT_FALSE(node->IsIsolatedThread());

    EXPECT_EQ(node->isIsolatedThread_, pipeline->isIsolatedThread_);
    auto* context = node->GetContext();
    EXPECT_NE(context, nullptr);

    node->isIsolatedThread_ = true;
    pipeline->isIsolatedThread_ = true;
    context = node->GetContext();
    EXPECT_NE(context, nullptr);
    EXPECT_TRUE(node->isIsolatedThread_);
    EXPECT_TRUE(pipeline->isIsolatedThread_);
}

/**
 * @tc.name: UINodeIsolatedThreadTest_GetContextVariantsMismatch001
 * @tc.desc: Test GetContext/GetAttachedContext/GetContextWithCheck all return context when node-pipeline mismatch
 * @tc.type: FUNC
 */
HWTEST_F(UINodeIsolatedThreadTest, UINodeIsolatedThreadTest_GetContextVariantsMismatch001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);

    auto node = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(node, nullptr);
    EXPECT_FALSE(node->isIsolatedThread_);

    pipeline->isIsolatedThread_ = true;

    auto* context = node->GetContext();
    EXPECT_NE(context, nullptr);

    node->AttachContext(AceType::RawPtr(pipeline), false);
    auto* attachedContext = node->GetAttachedContext();
    EXPECT_NE(attachedContext, nullptr);

    auto* contextWithCheck = node->GetContextWithCheck();
    EXPECT_NE(contextWithCheck, nullptr);
}

/**
 * @tc.name: UINodeIsolatedThreadTest_AttachContextMismatchAndImmutable001
 * @tc.desc: Test AttachContext with mismatch logs warning, and node's isIsolatedThread_ remains immutable
 * @tc.type: FUNC
 */
HWTEST_F(UINodeIsolatedThreadTest, UINodeIsolatedThreadTest_AttachContextMismatchAndImmutable001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);

    auto node = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(node, nullptr);
    EXPECT_FALSE(node->isIsolatedThread_);

    pipeline->isIsolatedThread_ = true;
    node->AttachContext(AceType::RawPtr(pipeline), false);

    EXPECT_FALSE(node->isIsolatedThread_);
    EXPECT_EQ(node->instanceId_, pipeline->GetInstanceId());
}

/**
 * @tc.name: UINodeIsolatedThreadTest_ChildOperationsMismatch001
 * @tc.desc: Test DoAddChild/AdoptChild with parent-child mismatch logs error, match works normally
 * @tc.type: FUNC
 */
HWTEST_F(UINodeIsolatedThreadTest, UINodeIsolatedThreadTest_ChildOperationsMismatch001, TestSize.Level1)
{
    auto parent = FrameNode::CreateFrameNode("parent", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(parent, nullptr);

    auto child = FrameNode::CreateFrameNode("child", 2, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(child, nullptr);

    parent->AddChild(child, 1);
    EXPECT_EQ(parent->children_.size(), 1);

    auto isolatedChild = FrameNode::CreateFrameNode("isolated_child", 3, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(isolatedChild, nullptr);
    isolatedChild->isIsolatedThread_ = true;

    parent->AddChild(isolatedChild, 2);
    EXPECT_EQ(parent->children_.size(), 2);

    parent->RemoveChild(isolatedChild);
    EXPECT_EQ(parent->children_.size(), 1);
    EXPECT_EQ(isolatedChild->GetParent(), nullptr);

    parent->AdoptChild(isolatedChild, true, true);
    EXPECT_EQ(parent->adoptedChildren_.size(), 1);
}
} // namespace OHOS::Ace::NG
