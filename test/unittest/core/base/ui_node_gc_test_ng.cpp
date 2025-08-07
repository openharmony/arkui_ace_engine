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
}