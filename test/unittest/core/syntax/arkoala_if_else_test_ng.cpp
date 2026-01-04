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

#include "frameworks/core/components_ng/syntax/arkoala_condition_scope.h"

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

class ConditionScopeNodeTest : public TestNG {
public:
    RefPtr<ConditionScopeNode> CreateIfElseNode(int32_t nodeId)
    {
        auto* stack = ViewStackProcessor::GetInstance();
        auto ifElseNode = AceType::MakeRefPtr<ConditionScopeNode>(nodeId);
        stack->Push(ifElseNode);
        return ifElseNode;
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
 * @tc.name: ArkoalaConditionScopeNodeTest001
 * @tc.desc: Test ArkoalaConditionScopeNode Create.
 * @tc.type: FUNC
 */
TEST_F(ConditionScopeNodeTest, ArkoalaConditionScopeNodeTest001)
{
    /**
     * @tc.steps: step1. Test ForEach node tag
     */
    int32_t nodeId = GetNextId();
    auto forEachNode = CreateIfElseNode(nodeId);
    EXPECT_NE(forEachNode, nullptr);

    EXPECT_EQ(forEachNode->GetTag(), V2::JS_IF_ELSE_ETS_TAG);
    EXPECT_EQ(forEachNode->GetId(), nodeId);
}

} // namespace OHOS::Ace::NG