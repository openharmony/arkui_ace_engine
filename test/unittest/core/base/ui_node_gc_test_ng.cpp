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
#define private public
#define protected public
#include "core/components_ng/base/ui_node_gc.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#undef private
#undef protected
using namespace testing;
using namespace testing::ext;

#include "interfaces/inner_api/ace_kit/src/view/ui_context_impl.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

namespace OHOS::Ace::NG {
class UINodeGCTestNg : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
    void SetUp() {};
    void TearDown() {};
};
 
/**
 * @tc.name: IsTooLateTest
 * @tc.desc: IsTooLate test
 * @tc.type: FUNC
 */
HWTEST_F(UINodeGCTestNg, IsTooLateTest, TestSize.Level1)
{
    auto ret = UiNodeGc::IsTooLate(-1);
    EXPECT_EQ(ret, false);
 
    ret = UiNodeGc::IsTooLate(0);
    EXPECT_EQ(ret, true);
}

/**
 * @tc.name: ReleaseInner
 * @tc.desc: ReleaseInner test
 * @tc.type: FUNC
 */
HWTEST_F(UINodeGCTestNg, ReleaseInnerTest, TestSize.Level1)
{
    auto& nodeRawBucket = UiNodeGc::MockGetNodeRawBucket();
    nodeRawBucket.push({
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, // 11 rawptr
    });
    EXPECT_EQ(nodeRawBucket.size(), 1);
    UiNodeGc::ReleaseInner(nullptr);
    EXPECT_EQ(nodeRawBucket.size(), 2);
    UiNodeGc::ReleaseNodeRawBucket();
    EXPECT_EQ(nodeRawBucket.size(), 1);
}

/**
 * @tc.name: JudgeGCLevelTest
 * @tc.desc: JudgeGCLevel test
 * @tc.type: FUNC
 */
HWTEST_F(UINodeGCTestNg, JudgeGCLevelTest, TestSize.Level1)
{
    auto ret = UiNodeGc::JudgeGCLevel(10, -1);
    EXPECT_EQ(ret, PriorityType::IDLE);
 
    ret = UiNodeGc::JudgeGCLevel(10, 0);
    EXPECT_EQ(ret, PriorityType::LOW);
 
    ret = UiNodeGc::JudgeGCLevel(80, 0);
    EXPECT_EQ(ret, PriorityType::HIGH);
 
    ret = UiNodeGc::JudgeGCLevel(300, 0);
    EXPECT_EQ(ret, PriorityType::IMMEDIATE);
 
    ret = UiNodeGc::JudgeGCLevel(600, 0);
    EXPECT_EQ(ret, PriorityType::VIP);
}
 
/**
 * @tc.name: ReleaseNodeRawBucketTest
 * @tc.desc: ReleaseNodeRawBucket test
 * @tc.type: FUNC
 */
HWTEST_F(UINodeGCTestNg, ReleaseNodeRawBucketTest, TestSize.Level1)
{
    auto& nodeRawBucket = UiNodeGc::MockGetNodeRawBucket();
    UiNodeGc::ReleaseNodeRawBucket();
    EXPECT_EQ(nodeRawBucket.size(), 0);
 
    RefPtr<Pattern> pattern;
    auto frameNode1 = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
                ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    frameNode1->uiNodeGcEnable_ = true;
    frameNode1 = nullptr;
    EXPECT_EQ(nodeRawBucket.size(), 1);
 
    auto frameNode2 = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
                ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    frameNode2->uiNodeGcEnable_ = true;
    frameNode2 = nullptr;
    EXPECT_EQ(nodeRawBucket.size(), 1);
 
    auto& bucket = nodeRawBucket.back();
    EXPECT_EQ(bucket.size(), 2);
 
    UiNodeGc::ReleaseNodeRawBucket();
    EXPECT_EQ(nodeRawBucket.size(), 0);
}
 
/**
 * @tc.name: ReleaseNodeRawMemoryInnerTest
 * @tc.desc: ReleaseNodeRawMemoryInner test
 * @tc.type: FUNC
 */
HWTEST_F(UINodeGCTestNg, ReleaseNodeRawMemoryInnerTest, TestSize.Level1)
{
    auto& nodeRawBucket = UiNodeGc::MockGetNodeRawBucket();
    UiNodeGc::ReleaseNodeRawMemoryInner(nullptr);
 
    RefPtr<Pattern> pattern;
    auto frameNode1 = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
                ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    frameNode1->uiNodeGcEnable_ = true;
    frameNode1 = nullptr;
    EXPECT_EQ(nodeRawBucket.size(), 1);
    UiNodeGc::ReleaseNodeRawMemory(1, nullptr);
    EXPECT_EQ(nodeRawBucket.size(), 1);

    UiNodeGc::ReleaseNodeRawMemory(-1, nullptr);
    EXPECT_EQ(nodeRawBucket.size(), 0);
}

/**
 * @tc.name: OnReleaseFunc
 * @tc.desc: OnReleaseFunc test
 * @tc.type: FUNC
 */
HWTEST_F(UINodeGCTestNg, OnReleaseFuncTest, TestSize.Level1)
{
    auto& nodeRawBucket = UiNodeGc::MockGetNodeRawBucket();
    UiNodeGc::OnReleaseFunc(nullptr);
    EXPECT_EQ(nodeRawBucket.size(), 0);
}

/**
 * @tc.name: UINode_OnDelete_OnMainTree_True
 * @tc.desc: OnDeleteTest_001
 * @tc.type: UINode will be off tree automaticly when node is attached on the tree
 */
HWTEST_F(UINodeGCTestNg, UINode_OnDelete_OnMainTree_True, TestSize.Level1)
{
    auto frameNode1 = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto context = std::make_shared<MockPipelineContext>();

    // enable UINodeGc
    frameNode1->RegisterReleaseFunc(true);
    frameNode1->onMainTree_ = false;
    frameNode1->nodeStatus_ = NodeStatus::BUILDER_NODE_OFF_MAINTREE;

    // attach node on main tree
    frameNode1->AttachToMainTree(false, context.get());

    EXPECT_TRUE(frameNode1->onMainTree_);
    EXPECT_EQ(frameNode1->nodeStatus_, NodeStatus::BUILDER_NODE_ON_MAINTREE);

    auto rawFrameNode1 = AceType::RawPtr(frameNode1);
    frameNode1 = nullptr;

    // frameNode1 is not released actually, we can use its raw ptr still
    EXPECT_FALSE(rawFrameNode1->onMainTree_);
    EXPECT_EQ(rawFrameNode1->nodeStatus_, NodeStatus::BUILDER_NODE_OFF_MAINTREE);

    // actually released in ReleaseNodeRawMemory
    UiNodeGc::ReleaseNodeRawMemory(-1, nullptr);
}

/**
 * @tc.name: UINode_OnDelete_OnMainTree_True_NodeStatus_True
 * @tc.desc: OnDeleteTest_001
 * @tc.type: UINode will be off tree automaticly when node is attached on the tree
 */
HWTEST_F(UINodeGCTestNg, UINode_OnDelete_OnMainTree_True_NodeStatus_True, TestSize.Level1)
{
    auto frameNode1 = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto context = std::make_shared<MockPipelineContext>();

    // enable UINodeGc
    frameNode1->RegisterReleaseFunc(true);
    frameNode1->onMainTree_ = false;
    frameNode1->nodeStatus_ = NodeStatus::BUILDER_NODE_OFF_MAINTREE;

    // attach node on main tree
    frameNode1->AttachToMainTree(false, context.get());

    EXPECT_TRUE(frameNode1->onMainTree_);
    EXPECT_EQ(frameNode1->nodeStatus_, NodeStatus::BUILDER_NODE_ON_MAINTREE);

    frameNode1->context_ = nullptr;
    frameNode1->nodeStatus_ = NodeStatus::BUILDER_NODE_OFF_MAINTREE;

    auto rawFrameNode1 = AceType::RawPtr(frameNode1);
    frameNode1 = nullptr;

    // frameNode1 is not released actually, we can use its raw ptr still
    EXPECT_FALSE(rawFrameNode1->onMainTree_);
    EXPECT_EQ(rawFrameNode1->nodeStatus_, NodeStatus::BUILDER_NODE_OFF_MAINTREE);

    // actually released in ReleaseNodeRawMemory
    UiNodeGc::ReleaseNodeRawMemory(-1, nullptr);
}


/**
 * @tc.name: UINode_OnDelete_OnMainTree_False
 * @tc.desc: OnDeleteTest_001
 * @tc.type: UINode will be off tree automaticly when node is attached on the tree
 */
HWTEST_F(UINodeGCTestNg, UINode_OnDelete_OnMainTree_False, TestSize.Level1)
{
    auto frameNode1 = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto context = std::make_shared<MockPipelineContext>();

    // enable UINodeGc
    frameNode1->RegisterReleaseFunc(true);
    frameNode1->onMainTree_ = false;
    frameNode1->nodeStatus_ = NodeStatus::BUILDER_NODE_OFF_MAINTREE;

    // not attach node on main tree
    EXPECT_FALSE(frameNode1->onMainTree_);
    EXPECT_EQ(frameNode1->nodeStatus_, NodeStatus::BUILDER_NODE_OFF_MAINTREE);

    auto rawFrameNode1 = AceType::RawPtr(frameNode1);
    frameNode1 = nullptr;

    // frameNode1 is not released actually, we can use its raw ptr still
    EXPECT_FALSE(rawFrameNode1->onMainTree_);
    EXPECT_EQ(rawFrameNode1->nodeStatus_, NodeStatus::BUILDER_NODE_OFF_MAINTREE);

    // actually released in ReleaseNodeRawMemory
    UiNodeGc::ReleaseNodeRawMemory(-1, nullptr);
}
} // namespace OHOS::Ace::NG