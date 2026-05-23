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

#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "base/utils/multi_thread.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class RichEditorMultiThreadTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
};

void RichEditorMultiThreadTestNg::SetUp()
{
    RichEditorCommonTestNg::SetUp();
}

void RichEditorMultiThreadTestNg::TearDown()
{
    RichEditorCommonTestNg::TearDown();
}

/**
 * @tc.name: OnAttachToFrameNodeMultiThread001
 * @tc.desc: Test RichEditorPattern::OnAttachToFrameNodeMultiThread with null host.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMultiThreadTestNg, OnAttachToFrameNodeMultiThread001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnAttachToFrameNodeMultiThread();
    EXPECT_EQ(pattern->richEditorInstanceId_, -1);
}

/**
 * @tc.name: OnAttachToFrameNodeMultiThread002
 * @tc.desc: Test RichEditorPattern::OnAttachToFrameNodeMultiThread with valid host (empty implementation).
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMultiThreadTestNg, OnAttachToFrameNodeMultiThread002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<RichEditorPattern>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(
        V2::RICH_EDITOR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), pattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    pattern->AttachToFrameNode(frameNode);

    pattern->OnAttachToFrameNodeMultiThread();
    EXPECT_EQ(pattern->frameId_, -1);
    EXPECT_TRUE(frameNode->afterAttachMainTreeTasks_.empty());
}

/**
 * @tc.name: OnDetachFromFrameNodeMultiThread001
 * @tc.desc: Test RichEditorPattern::OnDetachFromFrameNodeMultiThread with null node.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMultiThreadTestNg, OnDetachFromFrameNodeMultiThread001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnDetachFromFrameNodeMultiThread(nullptr);
    SUCCEED();
}

/**
 * @tc.name: OnDetachFromFrameNodeMultiThread002
 * @tc.desc: Test RichEditorPattern::OnDetachFromFrameNodeMultiThread with valid node (empty implementation).
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMultiThreadTestNg, OnDetachFromFrameNodeMultiThread002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<RichEditorPattern>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(
        V2::RICH_EDITOR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), pattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    pattern->AttachToFrameNode(frameNode);

    pattern->OnDetachFromFrameNodeMultiThread(AceType::RawPtr(frameNode));
    SUCCEED();
}

/**
 * @tc.name: OnAttachToMainTreeMultiThreadExtension001
 * @tc.desc: Test RichEditorPattern::OnAttachToMainTreeMultiThreadExtension with null host.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMultiThreadTestNg, OnAttachToMainTreeMultiThreadExtension001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnAttachToMainTreeMultiThreadExtension();
    SUCCEED();
}

/**
 * @tc.name: OnAttachToMainTreeMultiThreadExtension002
 * @tc.desc: Test RichEditorPattern::OnAttachToMainTreeMultiThreadExtension with valid host covers full logic.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMultiThreadTestNg, OnAttachToMainTreeMultiThreadExtension002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<RichEditorPattern>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(
        V2::RICH_EDITOR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), pattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    auto pipeline = MockPipelineContext::GetCurrent();
    frameNode->AttachContext(AceType::RawPtr(pipeline), true);
    pattern->AttachToFrameNode(frameNode);

    pattern->OnAttachToMainTreeMultiThreadExtension();
    EXPECT_TRUE(pattern->HasSurfaceChangedCallback() || pattern->HasSurfacePositionChangedCallback());
    EXPECT_NE(pattern->richEditorInstanceId_, -1);
    EXPECT_EQ(pattern->frameId_, frameNode->GetId());
}

/**
 * @tc.name: OnDetachFromMainTreeMultiThread001
 * @tc.desc: Test RichEditorPattern::OnDetachFromMainTreeMultiThread with null host.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMultiThreadTestNg, OnDetachFromMainTreeMultiThread001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnDetachFromMainTreeMultiThread();
    SUCCEED();
}

/**
 * @tc.name: OnDetachFromMainTreeMultiThread002
 * @tc.desc: Test RichEditorPattern::OnDetachFromMainTreeMultiThread with valid host.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMultiThreadTestNg, OnDetachFromMainTreeMultiThread002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<RichEditorPattern>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(
        V2::RICH_EDITOR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), pattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    auto pipeline = MockPipelineContext::GetCurrent();
    frameNode->AttachContext(AceType::RawPtr(pipeline), true);
    pattern->AttachToFrameNode(frameNode);
    pattern->frameId_ = frameNode->GetId();
    pattern->pipeline_ = WeakPtr<PipelineContext>(pipeline);

    pattern->OnDetachFromMainTreeMultiThread();
    SUCCEED();
}

/**
 * @tc.name: OnDetachFromMainTreeMultiThread003
 * @tc.desc: Test RichEditorPattern::OnDetachFromMainTreeMultiThread with selectOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMultiThreadTestNg, OnDetachFromMainTreeMultiThread003, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<RichEditorPattern>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(
        V2::RICH_EDITOR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), pattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    auto pipeline = MockPipelineContext::GetCurrent();
    frameNode->AttachContext(AceType::RawPtr(pipeline), true);
    pattern->AttachToFrameNode(frameNode);
    pattern->frameId_ = frameNode->GetId();
    pattern->pipeline_ = WeakPtr<PipelineContext>(pipeline);

    ASSERT_NE(pattern->selectOverlay_, nullptr);
    pattern->OnDetachFromMainTreeMultiThread();
    SUCCEED();
}

/**
 * @tc.name: ThreadSafeNodeCheck001
 * @tc.desc: Test THREAD_SAFE_NODE_CHECK in OnAttachToFrameNode redirects to empty MultiThread impl.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMultiThreadTestNg, ThreadSafeNodeCheck001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<RichEditorPattern>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(
        V2::RICH_EDITOR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), pattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    auto pipeline = MockPipelineContext::GetCurrent();
    frameNode->AttachContext(AceType::RawPtr(pipeline), true);
    pattern->AttachToFrameNode(frameNode);
    frameNode->isThreadSafeNode_ = true;
    frameNode->SetIsFree(true);

    pattern->OnAttachToFrameNode();
    EXPECT_EQ(pattern->frameId_, -1);
    EXPECT_TRUE(frameNode->afterAttachMainTreeTasks_.empty());
}

/**
 * @tc.name: ThreadSafeNodeCheck002
 * @tc.desc: Test THREAD_SAFE_NODE_CHECK in OnDetachFromFrameNode with ThreadSafeNode.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMultiThreadTestNg, ThreadSafeNodeCheck002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<RichEditorPattern>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(
        V2::RICH_EDITOR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), pattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    auto pipeline = MockPipelineContext::GetCurrent();
    frameNode->AttachContext(AceType::RawPtr(pipeline), true);
    pattern->AttachToFrameNode(frameNode);
    pattern->frameId_ = frameNode->GetId();
    pattern->pipeline_ = WeakPtr<PipelineContext>(pipeline);
    frameNode->isThreadSafeNode_ = true;

    pattern->OnDetachFromFrameNode(AceType::RawPtr(frameNode));
    SUCCEED();
}

/**
 * @tc.name: OnAttachToMainTreeMultiThreadExtension003
 * @tc.desc: Test OnAttachToMainTreeMultiThreadExtension sets contentNode and contentPattern.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMultiThreadTestNg, OnAttachToMainTreeMultiThreadExtension003, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<RichEditorPattern>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(
        V2::RICH_EDITOR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), pattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    auto pipeline = MockPipelineContext::GetCurrent();
    frameNode->AttachContext(AceType::RawPtr(pipeline), true);
    pattern->AttachToFrameNode(frameNode);

    pattern->OnAttachToMainTreeMultiThreadExtension();
    EXPECT_NE(pattern->contentPattern_, nullptr);
    EXPECT_EQ(frameNode->GetChildren().size(), 1);
}
} // namespace OHOS::Ace::NG
