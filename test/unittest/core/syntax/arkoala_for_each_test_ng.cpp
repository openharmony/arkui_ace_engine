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

#include "test/unittest/core/pattern/test_ng.h"

#include "frameworks/core/components_ng/syntax/arkoala_for_each_node.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class TestUINode : public UINode {
    DECLARE_ACE_TYPE(TestUINode, UINode);

    bool IsAtomicNode() const override
    {
        return true;
    }

    explicit TestUINode(int32_t nodeId) : UINode("TestUINode", nodeId) {}

    ~TestUINode() override = default;
};

class ArkoalaForEachNodeTest : public TestNG {
public:
    RefPtr<ArkoalaForEachNode> CreateForEachNode(int32_t nodeId)
    {
        auto* stack = ViewStackProcessor::GetInstance();
        auto forEachNode = AceType::MakeRefPtr<ArkoalaForEachNode>(nodeId);
        stack->Push(forEachNode);
        return forEachNode;
    }

    RefPtr<ArkoalaForEachNode> CreateRepeatNode(int32_t nodeId)
    {
        auto* stack = ViewStackProcessor::GetInstance();
        auto repeatNode = AceType::MakeRefPtr<ArkoalaForEachNode>(nodeId, true);
        stack->Push(repeatNode);
        return repeatNode;
    }

    RefPtr<TestUINode> CreateTestUINode(int32_t nodeId)
    {
        return AceType::MakeRefPtr<TestUINode>(nodeId);
    }

    RefPtr<FrameNode> CreateTestFrameNode(int32_t nodeId)
    {
        return FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, nodeId, AceType::MakeRefPtr<Pattern>());
    }

    std::string DumpUINode(const RefPtr<UINode>& node) const
    {
        return (node == nullptr) ? "null" : node->GetTag() + "(" + std::to_string(node->GetId()) + ")";
    }

    int32_t GetNextId()
    {
        return ++nodeId_;
    }

    int32_t nodeId_ = 0;
};

/**
 * @tc.name: ArkoalaForEachNodeTest001
 * @tc.desc: Test ArkoalaForEachNode Create.
 * @tc.type: FUNC
 */
TEST_F(ArkoalaForEachNodeTest, ArkoalaForEachNodeTest001)
{
    /**
     * @tc.steps: step1. Test ForEach node tag
     */
    int32_t nodeId1 = GetNextId();
    auto forEachNode = CreateForEachNode(nodeId1);
    EXPECT_NE(forEachNode, nullptr);

    EXPECT_EQ(forEachNode->GetTag(), V2::JS_FOR_EACH_ETS_TAG);
    EXPECT_EQ(forEachNode->GetId(), nodeId1);
    EXPECT_FALSE(forEachNode->isRepeat_);

    /**
     * @tc.steps: step2. Test Repeat node tag
     */
    int32_t nodeId2 = GetNextId();
    auto repeatNode = CreateRepeatNode(nodeId2);
    EXPECT_NE(repeatNode, nullptr);

    EXPECT_EQ(repeatNode->GetTag(), V2::JS_REPEAT_ETS_TAG);
    EXPECT_EQ(repeatNode->GetId(), nodeId2);
    EXPECT_TRUE(repeatNode->isRepeat_);
}

/**
 * @tc.name: ArkoalaForEachNodeTest002
 * @tc.desc: Test ArkoalaForEachNode DumpInfo.
 * @tc.type: FUNC
 */
TEST_F(ArkoalaForEachNodeTest, ArkoalaForEachNodeTest002)
{
    /**
     * @tc.steps: step1. Test ForEach node dump info
     */
    auto forEachNode = CreateForEachNode(GetNextId());
    EXPECT_NE(forEachNode, nullptr);
    forEachNode->DumpInfo();

    /**
     * @tc.steps: step2. Test Repeat node dump info
     */
    auto repeatNode = CreateRepeatNode(GetNextId());
    EXPECT_NE(repeatNode, nullptr);
    repeatNode->DumpInfo();
}

/**
 * @tc.name: SetOnMoveTest001
 * @tc.desc: Test ArkoalaForEachNode SetOnMove.
 * @tc.type: FUNC
 */
TEST_F(ArkoalaForEachNodeTest, SetOnMoveTest001)
{
    auto forEachNode = CreateForEachNode(GetNextId());
    EXPECT_NE(forEachNode, nullptr);
    auto setOnMoveCbFunc = [](int32_t from, int32_t to) {};
    forEachNode->SetOnMove(setOnMoveCbFunc);

    forEachNode->onMainTree_ = true;
    auto node = CreateTestFrameNode(GetNextId());
    forEachNode->SetParent(node);
    forEachNode->FlushUpdateAndMarkDirty();
    forEachNode->SetOnMove(setOnMoveCbFunc);
    forEachNode->SetOnMove(nullptr);
}
} // namespace OHOS::Ace::NG