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

#include "water_flow_test_ng.h"

#include "core/components_ng/pattern/waterflow/water_flow_item_model_ng.h"
#include "core/components_ng/pattern/waterflow/water_flow_item_pattern.h"

namespace OHOS::Ace::NG {

class WaterFlowItemModelTest : public WaterFlowTestNg {};

/**
 * @tc.name: CreateFrameNodeWithId001
 * @tc.desc: Test WaterFlowItemModelNG::CreateFrameNode(int32_t nodeId)
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowItemModelTest, CreateFrameNodeWithId001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FlowItem node with positive id.
     * @tc.expected: Node created with correct id, tag, and pattern type.
     */
    int32_t nodeId = 100;
    auto frameNode = WaterFlowItemModelNG::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetId(), nodeId);
    EXPECT_EQ(frameNode->GetTag(), "FlowItem");
    auto pattern = frameNode->GetPattern<WaterFlowItemPattern>();
    EXPECT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create FlowItem node with zero id.
     * @tc.expected: Node created with id 0.
     */
    auto frameNode2 = WaterFlowItemModelNG::CreateFrameNode(0);
    ASSERT_NE(frameNode2, nullptr);
    EXPECT_EQ(frameNode2->GetId(), 0);
    EXPECT_EQ(frameNode2->GetTag(), "FlowItem");

    /**
     * @tc.steps: step3. Create FlowItem node with negative id.
     * @tc.expected: Node created with negative id.
     */
    auto frameNode3 = WaterFlowItemModelNG::CreateFrameNode(-1);
    ASSERT_NE(frameNode3, nullptr);
    EXPECT_EQ(frameNode3->GetId(), -1);
    auto pattern3 = frameNode3->GetPattern<WaterFlowItemPattern>();
    EXPECT_NE(pattern3, nullptr);
}

/**
 * @tc.name: Create001
 * @tc.desc: Test WaterFlowItemModelNG::Create() pushes node onto ViewStack
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowItemModelTest, Create001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call Create() to push FlowItem onto ViewStack.
     * @tc.expected: Top of ViewStack is a FlowItem with correct tag and pattern.
     */
    WaterFlowItemModelNG itemModel;
    itemModel.Create();
    auto topNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(topNode, nullptr);
    EXPECT_EQ(topNode->GetTag(), "FlowItem");
    auto pattern = topNode->GetPattern<WaterFlowItemPattern>();
    EXPECT_NE(pattern, nullptr);
    ViewStackProcessor::GetInstance()->FlushImplicitAnimation();
    ViewStackProcessor::GetInstance()->Finish();
}

/**
 * @tc.name: CreateFrameNodeDistinct001
 * @tc.desc: Test WaterFlowItemModelNG::CreateFrameNode(nodeId) creates distinct nodes for different IDs
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowItemModelTest, CreateFrameNodeDistinct001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create two FlowItem nodes with different ids.
     * @tc.expected: Nodes are distinct objects with different ids.
     */
    auto node1 = WaterFlowItemModelNG::CreateFrameNode(10);
    auto node2 = WaterFlowItemModelNG::CreateFrameNode(20);
    ASSERT_NE(node1, nullptr);
    ASSERT_NE(node2, nullptr);
    EXPECT_NE(node1, node2);
    EXPECT_EQ(node1->GetId(), 10);
    EXPECT_EQ(node2->GetId(), 20);
    EXPECT_EQ(node1->GetTag(), "FlowItem");
    EXPECT_EQ(node2->GetTag(), "FlowItem");
}
} // namespace OHOS::Ace::NG
