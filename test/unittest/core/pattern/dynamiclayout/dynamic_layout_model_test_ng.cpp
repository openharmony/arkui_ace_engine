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

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#define private public
#define protected public
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/dynamiclayout/dynamic_layout_model_ng.h"
#include "core/components_ng/pattern/dynamiclayout/dynamic_layout_node.h"
#include "core/components_ng/pattern/dynamiclayout/dynamic_layout_pattern.h"
#include "core/components_ng/pattern/dynamiclayout/algorithm_param_base.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/stack/stack_layout_property.h"
#include "core/pipeline/base/element_register.h"
#include "core/components_ng/pattern/dynamiclayout/algorithm_param_base.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_NODE_ID = 100;
const std::string TEST_TAG = "DynamicLayout";
constexpr float TEST_SPACE_VALUE = 10.0f;
constexpr bool TEST_IS_REVERSE = true;
}

class DynamicLayoutModelTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
    }
    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
    }
    void SetUp() override
    {
        ViewStackProcessor::GetInstance()->ClearStack();
    }
    void TearDown() override
    {
        ViewStackProcessor::GetInstance()->ClearStack();
        ElementRegister::GetInstance()->Clear();
    }
};

/**
 * @tc.name: DynamicLayoutModelNG_Create_ColumnLayout_001
 * @tc.desc: Test Create with COLUMN_LAYOUT type
 * @tc.type: FUNC
 */
HWTEST_F(DynamicLayoutModelTestNg, DynamicLayoutModelNG_Create_ColumnLayout_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LinearLayoutAlgorithmParam for column
     */
    auto columnParams = AceType::MakeRefPtr<LinearLayoutAlgorithmParam>(true);

    /**
     * @tc.steps: step2. Call DynamicLayoutModelNG::Create with COLUMN_LAYOUT
     */
    DynamicLayoutModelNG model;
    model.Create(columnParams, DynamicLayoutType::COLUMN_LAYOUT);

    /**
     * @tc.steps: step3. Verify frameNode is created and pushed to stack
     * @tc.expected: FrameNode should be created with correct pattern
     */
    auto frameNode = AceType::DynamicCast<DynamicLayoutNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);

    auto layoutType = frameNode->GetLayoutType();
    EXPECT_EQ(layoutType, DynamicLayoutType::COLUMN_LAYOUT);
}

/**
 * @tc.name: DynamicLayoutModelNG_Create_RowLayout_001
 * @tc.desc: Test Create with ROW_LAYOUT type
 * @tc.type: FUNC
 */
HWTEST_F(DynamicLayoutModelTestNg, DynamicLayoutModelNG_Create_RowLayout_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LinearLayoutAlgorithmParam for row
     */
    auto rowParams = AceType::MakeRefPtr<LinearLayoutAlgorithmParam>(false);

    /**
     * @tc.steps: step2. Call DynamicLayoutModelNG::Create with ROW_LAYOUT
     */
    DynamicLayoutModelNG model;
    model.Create(rowParams, DynamicLayoutType::ROW_LAYOUT);

    /**
     * @tc.steps: step3. Verify frameNode is created and pushed to stack
     * @tc.expected: FrameNode should be created with correct pattern
     */
    auto frameNode = AceType::DynamicCast<DynamicLayoutNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);

    auto layoutType = frameNode->GetLayoutType();
    EXPECT_EQ(layoutType, DynamicLayoutType::ROW_LAYOUT);
}

/**
 * @tc.name: DynamicLayoutModelNG_Create_StackLayout_001
 * @tc.desc: Test Create with STACK_LAYOUT type
 * @tc.type: FUNC
 */
HWTEST_F(DynamicLayoutModelTestNg, DynamicLayoutModelNG_Create_StackLayout_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create StackLayoutAlgorithmParam
     */
    auto stackParams = AceType::MakeRefPtr<StackLayoutAlgorithmParam>();

    /**
     * @tc.steps: step2. Call DynamicLayoutModelNG::Create with STACK_LAYOUT
     */
    DynamicLayoutModelNG model;
    model.Create(stackParams, DynamicLayoutType::STACK_LAYOUT);

    /**
     * @tc.steps: step3. Verify frameNode is created and pushed to stack
     * @tc.expected: FrameNode should be created with correct pattern
     */
    auto frameNode = AceType::DynamicCast<DynamicLayoutNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);

    auto layoutType = frameNode->GetLayoutType();
    EXPECT_EQ(layoutType, DynamicLayoutType::STACK_LAYOUT);
}

/**
 * @tc.name: DynamicLayoutModelNG_Create_CustomLayout_001
 * @tc.desc: Test Create with CUSTOM_LAYOUT type
 * @tc.type: FUNC
 */
HWTEST_F(DynamicLayoutModelTestNg, DynamicLayoutModelNG_Create_CustomLayout_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CustomLayoutAlgorithmParam
     */
    auto customParams = AceType::MakeRefPtr<CustomLayoutAlgorithmParam>();

    /**
     * @tc.steps: step2. Call DynamicLayoutModelNG::Create with CUSTOM_LAYOUT
     */
    DynamicLayoutModelNG model;
    model.Create(customParams, DynamicLayoutType::CUSTOM_LAYOUT);

    /**
     * @tc.steps: step3. Verify frameNode is created and pushed to stack
     * @tc.expected: FrameNode should be created with DynamicLayoutPattern
     */
    auto frameNode = AceType::DynamicCast<DynamicLayoutNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);

    auto layoutType = frameNode->GetLayoutType();
    EXPECT_EQ(layoutType, DynamicLayoutType::CUSTOM_LAYOUT);

    auto pattern = frameNode->GetPattern<DynamicLayoutPattern>();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: DynamicLayoutModelNG_Create_DefaultLayout_001
 * @tc.desc: Test Create with DEFAULT_LAYOUT type
 * @tc.type: FUNC
 */
HWTEST_F(DynamicLayoutModelTestNg, DynamicLayoutModelNG_Create_DefaultLayout_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create AlgorithmParamBase with default type
     */
    auto defaultParams = AceType::MakeRefPtr<AlgorithmParamBase>();

    /**
     * @tc.steps: step2. Call DynamicLayoutModelNG::Create with DEFAULT_LAYOUT
     */
    DynamicLayoutModelNG model;
    model.Create(defaultParams, DynamicLayoutType::DEFAULT_LAYOUT);

    /**
     * @tc.steps: step3. Verify frameNode is created and pushed to stack
     * @tc.expected: FrameNode should be created with default DynamicLayoutPattern
     */
    auto frameNode = AceType::DynamicCast<DynamicLayoutNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);

    auto layoutType = frameNode->GetLayoutType();
    EXPECT_EQ(layoutType, DynamicLayoutType::DEFAULT_LAYOUT);
}

/**
 * @tc.name: DynamicLayoutModelNG_UpdatePropertyFromLinearParam_001
 * @tc.desc: Test UpdatePropertyFromAlgorithmParams for COLUMN_LAYOUT type
 * @tc.type: FUNC
 */
HWTEST_F(DynamicLayoutModelTestNg, DynamicLayoutModelNG_UpdatePropertyFromLinearParam_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and LinearLayoutAlgorithmParam
     */
    auto pattern = AceType::MakeRefPtr<LinearLayoutPattern>(true);
    auto frameNode = FrameNode::CreateFrameNode(TEST_TAG, TEST_NODE_ID, pattern, false);
    ASSERT_NE(frameNode, nullptr);

    auto linearParams = AceType::MakeRefPtr<LinearLayoutAlgorithmParam>(true);
    CalcDimension testSpace(TEST_SPACE_VALUE, DimensionUnit::VP);
    linearParams->SetSpace(testSpace);
    linearParams->SetMainAxisAlign(FlexAlign::CENTER);
    linearParams->SetCrossAxisAlign(FlexAlign::FLEX_END);
    linearParams->SetIsReverse(TEST_IS_REVERSE);

    /**
     * @tc.steps: step2. Call UpdatePropertyFromAlgorithmParams with COLUMN_LAYOUT type
     */
    DynamicLayoutModelNG::UpdatePropertyFromAlgorithmParams(frameNode, linearParams, DynamicLayoutType::COLUMN_LAYOUT);

    /**
     * @tc.steps: step3. Verify properties are updated
     * @tc.expected: LayoutProperty should contain updated values
     */
    auto layoutProperty = frameNode->GetLayoutProperty<LinearLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: DynamicLayoutModelNG_UpdatePropertyFromStackParam_001
 * @tc.desc: Test UpdatePropertyFromAlgorithmParams for STACK_LAYOUT type
 * @tc.type: FUNC
 */
HWTEST_F(DynamicLayoutModelTestNg, DynamicLayoutModelNG_UpdatePropertyFromStackParam_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and StackLayoutAlgorithmParam
     */
    auto pattern = AceType::MakeRefPtr<StackPattern>();
    auto frameNode = FrameNode::CreateFrameNode(TEST_TAG, TEST_NODE_ID, pattern, false);
    ASSERT_NE(frameNode, nullptr);

    auto stackParams = AceType::MakeRefPtr<StackLayoutAlgorithmParam>(Alignment::TOP_LEFT);

    /**
     * @tc.steps: step2. Call UpdatePropertyFromAlgorithmParams with STACK_LAYOUT type
     */
    DynamicLayoutModelNG::UpdatePropertyFromAlgorithmParams(frameNode, stackParams, DynamicLayoutType::STACK_LAYOUT);

    /**
     * @tc.steps: step3. Verify properties are updated
     * @tc.expected: StackLayoutProperty should exist
     */
    auto layoutProperty = frameNode->GetLayoutProperty<StackLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: DynamicLayoutNode_GetOrCreateDynamicLayoutNode_001
 * @tc.desc: Test GetOrCreateDynamicLayoutNode when node does not exist
 * @tc.type: FUNC
 */
HWTEST_F(DynamicLayoutModelTestNg, DynamicLayoutNode_GetOrCreateDynamicLayoutNode_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call GetOrCreateDynamicLayoutNode with new nodeId
     */
    auto patternCreator = []() -> RefPtr<Pattern> {
        return AceType::MakeRefPtr<DynamicLayoutPattern>();
    };

    auto [node, isInitialRender] = DynamicLayoutNode::GetOrCreateDynamicLayoutNode(
        TEST_TAG, TEST_NODE_ID, patternCreator);

    /**
     * @tc.steps: step2. Verify node is created
     * @tc.expected: Should return new node with isInitialRender=true
     */
    ASSERT_NE(node, nullptr);
    EXPECT_TRUE(isInitialRender);
    EXPECT_EQ(node->GetTag(), TEST_TAG);
}

/**
 * @tc.name: DynamicLayoutNode_GetOrCreateDynamicLayoutNode_002
 * @tc.desc: Test GetOrCreateDynamicLayoutNode when node already exists
 * @tc.type: FUNC
 */
HWTEST_F(DynamicLayoutModelTestNg, DynamicLayoutNode_GetOrCreateDynamicLayoutNode_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create node first time
     */
    auto patternCreator = []() -> RefPtr<Pattern> {
        return AceType::MakeRefPtr<DynamicLayoutPattern>();
    };

    auto [node1, isInitialRender1] = DynamicLayoutNode::GetOrCreateDynamicLayoutNode(
        TEST_TAG, TEST_NODE_ID, patternCreator);
    ASSERT_NE(node1, nullptr);
    EXPECT_TRUE(isInitialRender1);

    /**
     * @tc.steps: step2. Call GetOrCreateDynamicLayoutNode with same nodeId
     */
    auto [node2, isInitialRender2] = DynamicLayoutNode::GetOrCreateDynamicLayoutNode(
        TEST_TAG, TEST_NODE_ID, patternCreator);

    /**
     * @tc.steps: step3. Verify existing node is returned
     * @tc.expected: Should return same node with isInitialRender=false
     */
    EXPECT_EQ(node1, node2);
    EXPECT_FALSE(isInitialRender2);
}

/**
 * @tc.name: DynamicLayoutNode_SetAndGetLayoutType_001
 * @tc.desc: Test SetLayoutType and GetLayoutType
 * @tc.type: FUNC
 */
HWTEST_F(DynamicLayoutModelTestNg, DynamicLayoutNode_SetAndGetLayoutType_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DynamicLayoutNode
     */
    auto pattern = AceType::MakeRefPtr<DynamicLayoutPattern>();
    auto node = AceType::MakeRefPtr<DynamicLayoutNode>(TEST_TAG, TEST_NODE_ID, pattern, false);

    /**
     * @tc.steps: step2. Set different layout types and verify
     * @tc.expected: GetLayoutType should return the set value
     */
    node->SetLayoutType(DynamicLayoutType::COLUMN_LAYOUT);
    EXPECT_EQ(node->GetLayoutType(), DynamicLayoutType::COLUMN_LAYOUT);

    node->SetLayoutType(DynamicLayoutType::ROW_LAYOUT);
    EXPECT_EQ(node->GetLayoutType(), DynamicLayoutType::ROW_LAYOUT);

    node->SetLayoutType(DynamicLayoutType::STACK_LAYOUT);
    EXPECT_EQ(node->GetLayoutType(), DynamicLayoutType::STACK_LAYOUT);

    node->SetLayoutType(DynamicLayoutType::CUSTOM_LAYOUT);
    EXPECT_EQ(node->GetLayoutType(), DynamicLayoutType::CUSTOM_LAYOUT);
}

/**
 * @tc.name: DynamicLayoutModelNG_UpdatePropertyFromAlgorithmParams_001
 * @tc.desc: Test UpdatePropertyFromAlgorithmParams for each supported type
 * @tc.type: FUNC
 */
HWTEST_F(DynamicLayoutModelTestNg, DynamicLayoutModelNG_UpdatePropertyFromAlgorithmParams_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode with LinearLayoutPattern
     */
    auto pattern = AceType::MakeRefPtr<LinearLayoutPattern>(true);
    auto frameNode = FrameNode::CreateFrameNode(TEST_TAG, TEST_NODE_ID, pattern, false);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Test COLUMN_LAYOUT update
     */
    auto columnParams = AceType::MakeRefPtr<LinearLayoutAlgorithmParam>(true);
    DynamicLayoutModelNG::UpdatePropertyFromAlgorithmParams(frameNode, columnParams, DynamicLayoutType::COLUMN_LAYOUT);
    auto layoutProperty = frameNode->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step3. Test ROW_LAYOUT update
     */
    auto rowParams = AceType::MakeRefPtr<LinearLayoutAlgorithmParam>(false);
    DynamicLayoutModelNG::UpdatePropertyFromAlgorithmParams(frameNode, rowParams, DynamicLayoutType::ROW_LAYOUT);

    /**
     * @tc.steps: step4. Test CUSTOM_LAYOUT (should not crash, but no update)
     */
    auto customParams = AceType::MakeRefPtr<CustomLayoutAlgorithmParam>();
    DynamicLayoutModelNG::UpdatePropertyFromAlgorithmParams(frameNode, customParams, DynamicLayoutType::CUSTOM_LAYOUT);
}

/**
 * @tc.name: DynamicLayoutModelNG_Create_WithLinearParams_001
 * @tc.desc: Test Create with linear layout params containing space and alignment
 * @tc.type: FUNC
 */
HWTEST_F(DynamicLayoutModelTestNg, DynamicLayoutModelNG_Create_WithLinearParams_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LinearLayoutAlgorithmParam with full configuration
     */
    CalcDimension space(TEST_SPACE_VALUE, DimensionUnit::VP);
    auto linearParams = AceType::MakeRefPtr<LinearLayoutAlgorithmParam>(
        space, FlexAlign::CENTER, FlexAlign::FLEX_END);
    linearParams->SetIsReverse(TEST_IS_REVERSE);

    /**
     * @tc.steps: step2. Create DynamicLayout with COLUMN type
     */
    DynamicLayoutModelNG model;
    model.Create(linearParams, DynamicLayoutType::COLUMN_LAYOUT);

    /**
     * @tc.steps: step3. Verify frameNode is created
     * @tc.expected: FrameNode should be created with correct layout type
     */
    auto frameNode = AceType::DynamicCast<DynamicLayoutNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetLayoutType(), DynamicLayoutType::COLUMN_LAYOUT);
}

} // namespace OHOS::Ace::NG
