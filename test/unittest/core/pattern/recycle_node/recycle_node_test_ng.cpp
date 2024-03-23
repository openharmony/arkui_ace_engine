/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "gtest/hwext/gtest-ext.h"

#include "base/memory/ace_type.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/pattern/recycle_view/recycle_dummy_node.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class RecycleNodeTestNG : public testing::Test {};
/**
 * @tc.name: RecycleNodeTestNg001
 * @tc.desc: destructor RecycleNode
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(RecycleNodeTestNG, RecycleNodeTestNG001, TestSize.Level1)
{
    int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    int32_t childNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    /**
     * @tc.steps: step1. Create RecycleNode width no child.
     * @tc.expected: expect not recycle any child.
     */
    auto recycleNode0 = RecycleDummyNode::CreateRecycleDummyNode(nodeId);
    EXPECT_EQ(recycleNode0->TotalChildCount(), 0);
    recycleNode0.Reset();

    /**
     * @tc.steps: step2. Create RecycleNode width a custom node child.
     * @tc.expected: expect recycle custom node.
     */
    nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto recycleNode1 = RecycleDummyNode::CreateRecycleDummyNode(nodeId);
    std::string childNodeName = "childNode";
    auto childCustomNode = CustomNode::CreateCustomNode(childNodeId, childNodeName);
    auto child = recycleNode1->GetFirstChild();
    EXPECT_EQ(child, nullptr);
    auto mockRecycleFunc = [childCustomNode](RefPtr<CustomNodeBase> node) { EXPECT_EQ(childCustomNode, node); };
    childCustomNode->SetRecycleFunction(std::move(mockRecycleFunc));
    recycleNode1->AddChild(childCustomNode);
    recycleNode1.Reset();

    /**
     * @tc.steps: step3. Create RecycleNode width a child but not custom node.
     * @tc.expected: expect not recycle any child.
     */
    nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    childNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto recycleNode2 = RecycleDummyNode::CreateRecycleDummyNode(nodeId);
    auto frameNodeChild = FrameNode::CreateFrameNode("child", childNodeId, AceType::MakeRefPtr<Pattern>());
    recycleNode2->AddChild(frameNodeChild);
    auto child2 = recycleNode2->GetFirstChild();
    auto customNode2 = AceType::DynamicCast<CustomNodeBase>(child2);
    EXPECT_EQ(customNode2, nullptr);
    recycleNode2.Reset();
}
} // namespace OHOS::Ace::NG
