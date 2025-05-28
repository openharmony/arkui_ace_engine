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
#include "ui/base/ace_type.h"

#include "core/pipeline/base/element_register.h"
#define protected public
#define private public

#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/base/node_render_status_monitor.h"

#undef private
#undef protected

namespace OHOS::Ace::NG {

class NodeRenderStatusMonitorTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp();
    void TearDown() {};

protected:
    RefPtr<NodeRenderStatusMonitor> monitor_;
};

void NodeRenderStatusMonitorTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void NodeRenderStatusMonitorTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

void NodeRenderStatusMonitorTestNg::SetUp()
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    monitor_ = context->GetNodeRenderStatusMonitor();
}

/**
 * @tc.name: NodeRenderStatusMonitorTestNg001
 * @tc.desc: Test RegisterNodeRenderStatusListener UnRegisterNodeRenderStatusListener
 * @tc.type: FUNC
 */
HWTEST_F(NodeRenderStatusMonitorTestNg, NodeRenderStatusMonitorTestNg001, testing::ext::TestSize.Level1)
{
    ASSERT_NE(monitor_, nullptr);
    auto frameNodeOne = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(frameNodeOne, nullptr);
    auto func = [](FrameNode* frameNode, NodeRenderState state, RenderMonitorReason reason) {};
    auto frameNodeOnePtr = AceType::RawPtr(frameNodeOne);
    auto resultOne = monitor_->RegisterNodeRenderStatusListener(frameNodeOnePtr, func, MonitorSourceType::OBSERVER);
    auto resultOneId = resultOne.id;
    EXPECT_NE(resultOne.id, MONITOR_INVALID_ID);
    EXPECT_EQ(monitor_->nodeRenderStatusListeners_.size(), 1);

    resultOne = monitor_->RegisterNodeRenderStatusListener(frameNodeOnePtr, func, MonitorSourceType::OBSERVER);
    EXPECT_EQ(resultOne.id, MONITOR_INVALID_ID);
    EXPECT_EQ(monitor_->nodeRenderStatusListeners_.size(), 1);

    resultOne = monitor_->RegisterNodeRenderStatusListener(nullptr, func, MonitorSourceType::OBSERVER);
    EXPECT_EQ(resultOne.id, MONITOR_INVALID_ID);
    EXPECT_EQ(monitor_->nodeRenderStatusListeners_.size(), 1);

    auto frameNodeTwo = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(frameNodeTwo, nullptr);
    auto frameNodeTwoPtr = AceType::RawPtr(frameNodeTwo);
    auto resultTwo = monitor_->RegisterNodeRenderStatusListener(frameNodeTwoPtr, nullptr, MonitorSourceType::OBSERVER);
    EXPECT_EQ(resultTwo.id, MONITOR_INVALID_ID);
    EXPECT_EQ(monitor_->nodeRenderStatusListeners_.size(), 1);

    resultTwo = monitor_->RegisterNodeRenderStatusListener(frameNodeTwoPtr, func, MonitorSourceType::OBSERVER);
    EXPECT_NE(resultTwo.id, MONITOR_INVALID_ID);
    EXPECT_EQ(monitor_->nodeRenderStatusListeners_.size(), 2);
    monitor_->UnRegisterNodeRenderStatusListener(frameNodeOnePtr, resultOneId);
    EXPECT_EQ(monitor_->nodeRenderStatusListeners_.size(), 1);
    monitor_->UnRegisterNodeRenderStatusListener(frameNodeOnePtr, resultOneId);
    EXPECT_EQ(monitor_->nodeRenderStatusListeners_.size(), 1);
    monitor_->UnRegisterNodeRenderStatusListener(frameNodeTwoPtr, resultTwo.id);
    EXPECT_EQ(monitor_->nodeRenderStatusListeners_.size(), 0);
}

/**
 * @tc.name: NodeRenderStatusMonitorTestNg002
 * @tc.desc: Test WalkThroughAncestorForStateListener
 * @tc.type: FUNC
 */
HWTEST_F(NodeRenderStatusMonitorTestNg, NodeRenderStatusMonitorTestNg002, testing::ext::TestSize.Level1)
{
    ASSERT_NE(monitor_, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(rootNode, nullptr);
    rootNode->layoutProperty_->UpdateVisibility(OHOS::Ace::VisibleType::VISIBLE);
    rootNode->SetActive(true);
    auto childNodeOne = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(childNodeOne, nullptr);
    childNodeOne->layoutProperty_->UpdateVisibility(OHOS::Ace::VisibleType::VISIBLE);
    childNodeOne->SetActive(true);
    childNodeOne->AttachToMainTree(true);
    childNodeOne->MountToParent(rootNode);
    rootNode->AttachToMainTree(true);
    int32_t listenerCount = 0;
    auto func = [&listenerCount](
                    FrameNode* frameNode, NodeRenderState state, RenderMonitorReason reason) { listenerCount++; };
    auto childNodeOnePtr = AceType::RawPtr(childNodeOne);
    auto result = monitor_->RegisterNodeRenderStatusListener(childNodeOnePtr, func, MonitorSourceType::OBSERVER);
    EXPECT_EQ(result.state, NodeRenderState::ABOUT_TO_RENDER_IN);

    childNodeOne->layoutProperty_->UpdateVisibility(OHOS::Ace::VisibleType::INVISIBLE);
    auto state = monitor_->GetNodeCurrentRenderState(childNodeOnePtr);
    EXPECT_EQ(state, NodeRenderState::ABOUT_TO_RENDER_OUT);
    monitor_->WalkThroughAncestorForStateListener();
    EXPECT_EQ(listenerCount, 1);

    auto childNodeTwo = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(childNodeTwo, nullptr);
    childNodeTwo->layoutProperty_->UpdateVisibility(OHOS::Ace::VisibleType::VISIBLE);
    childNodeTwo->SetActive(true);
    childNodeTwo->AttachToMainTree(true);
    childNodeTwo->MountToParent(childNodeOne);
    auto childNodeTwoPtr = AceType::RawPtr(childNodeTwo);
    state = monitor_->GetNodeCurrentRenderState(childNodeTwoPtr);
    EXPECT_EQ(state, NodeRenderState::ABOUT_TO_RENDER_OUT);
    childNodeOne->layoutProperty_->UpdateVisibility(OHOS::Ace::VisibleType::VISIBLE);
    state = monitor_->GetNodeCurrentRenderState(childNodeTwoPtr);
    EXPECT_EQ(state, NodeRenderState::ABOUT_TO_RENDER_IN);
    monitor_->UnRegisterNodeRenderStatusListener(childNodeOnePtr, result.id);
    EXPECT_EQ(monitor_->nodeRenderStatusListeners_.size(), 0);
}

/**
 * @tc.name: NodeRenderStatusMonitorTestNg003
 * @tc.desc: Test GetNodeCurrentRenderState
 * @tc.type: FUNC
 */
HWTEST_F(NodeRenderStatusMonitorTestNg, NodeRenderStatusMonitorTestNg003, testing::ext::TestSize.Level1)
{
    ASSERT_NE(monitor_, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(rootNode, nullptr);
    rootNode->layoutProperty_->UpdateVisibility(OHOS::Ace::VisibleType::VISIBLE);
    rootNode->SetActive(true);
    auto func = [](FrameNode* frameNode, NodeRenderState state, RenderMonitorReason reason) {};
    auto childNodeOne = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(childNodeOne, nullptr);
    childNodeOne->layoutProperty_->UpdateVisibility(OHOS::Ace::VisibleType::VISIBLE);
    childNodeOne->SetActive(true);
    rootNode->AddChild(childNodeOne);
    auto childNodeOnePtr = AceType::RawPtr(childNodeOne);
    rootNode->AttachToMainTree(true);
    auto result = monitor_->RegisterNodeRenderStatusListener(childNodeOnePtr, func, MonitorSourceType::OBSERVER);
    auto state = monitor_->GetNodeCurrentRenderState(childNodeOnePtr);
    EXPECT_EQ(state, NodeRenderState::ABOUT_TO_RENDER_IN);

    childNodeOne->layoutProperty_->UpdateVisibility(OHOS::Ace::VisibleType::INVISIBLE);
    state = monitor_->GetNodeCurrentRenderState(childNodeOnePtr);
    EXPECT_EQ(state, NodeRenderState::ABOUT_TO_RENDER_OUT);

    childNodeOne->layoutProperty_->UpdateVisibility(OHOS::Ace::VisibleType::VISIBLE);
    childNodeOne->SetActive(false);
    state = monitor_->GetNodeCurrentRenderState(childNodeOnePtr);
    EXPECT_EQ(state, NodeRenderState::ABOUT_TO_RENDER_OUT);

    childNodeOne->SetActive(true);
    childNodeOne->onMainTree_ = false;
    state = monitor_->GetNodeCurrentRenderState(childNodeOnePtr);
    EXPECT_EQ(state, NodeRenderState::ABOUT_TO_RENDER_OUT);

    monitor_->UnRegisterNodeRenderStatusListener(childNodeOnePtr, result.id);
    EXPECT_EQ(monitor_->nodeRenderStatusListeners_.size(), 0);
}

/**
 * @tc.name: NodeRenderStatusMonitorTestNg004
 * @tc.desc: Test NotifyFrameNodeRelease
 * @tc.type: FUNC
 */
HWTEST_F(NodeRenderStatusMonitorTestNg, NodeRenderStatusMonitorTestNg004, testing::ext::TestSize.Level1)
{
    ASSERT_NE(monitor_, nullptr);
    auto func = [](FrameNode* frameNode, NodeRenderState state, RenderMonitorReason reason) {};
    auto childNodeOne = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(childNodeOne, nullptr);
    monitor_->RegisterNodeRenderStatusListener(AceType::RawPtr(childNodeOne), func, MonitorSourceType::OBSERVER);
    auto childNodeTwo = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(childNodeTwo, nullptr);
    monitor_->RegisterNodeRenderStatusListener(AceType::RawPtr(childNodeTwo), func, MonitorSourceType::OBSERVER);
    EXPECT_EQ(monitor_->nodeRenderStatusListeners_.size(), 2);
    childNodeOne.Reset();
    EXPECT_EQ(monitor_->nodeRenderStatusListeners_.size(), 1);
    childNodeTwo.Reset();
    EXPECT_EQ(monitor_->nodeRenderStatusListeners_.size(), 0);
}

/**
 * @tc.name: NodeRenderStatusMonitorTestNg005
 * @tc.desc: Test IsRegisterNodeRenderStateChangeCallbackExceedLimit
 * @tc.type: FUNC
 */
HWTEST_F(NodeRenderStatusMonitorTestNg, NodeRenderStatusMonitorTestNg005, testing::ext::TestSize.Level1)
{
    ASSERT_NE(monitor_, nullptr);
    std::vector<RefPtr<FrameNode>> frameNodes;
    auto func = [](FrameNode* frameNode, NodeRenderState state, RenderMonitorReason reason) {};
    for (int i = 0; i < 63; i++) {
        auto child = FrameNode::CreateFrameNode(
            V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
        ASSERT_NE(child, nullptr);
        frameNodes.emplace_back(child);
        monitor_->RegisterNodeRenderStatusListener(AceType::RawPtr(child), func, MonitorSourceType::OBSERVER);
    }
    EXPECT_EQ(monitor_->nodeRenderStatusListeners_.size(), 63);
    bool isLimit = monitor_->IsRegisterNodeRenderStateChangeCallbackExceedLimit();
    EXPECT_EQ(isLimit, false);

    auto child = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(child, nullptr);
    auto result = monitor_->RegisterNodeRenderStatusListener(AceType::RawPtr(child), func, MonitorSourceType::OBSERVER);
    EXPECT_NE(result.id, MONITOR_INVALID_ID);
    EXPECT_EQ(monitor_->nodeRenderStatusListeners_.size(), 64);
    isLimit = monitor_->IsRegisterNodeRenderStateChangeCallbackExceedLimit();
    EXPECT_EQ(isLimit, true);

    auto childTwo = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(childTwo, nullptr);
    result = monitor_->RegisterNodeRenderStatusListener(AceType::RawPtr(childTwo), func, MonitorSourceType::OBSERVER);
    EXPECT_EQ(result.id, MONITOR_INVALID_ID);
    isLimit = monitor_->IsRegisterNodeRenderStateChangeCallbackExceedLimit();
    EXPECT_EQ(isLimit, true);
}
} // namespace OHOS::Ace::NG